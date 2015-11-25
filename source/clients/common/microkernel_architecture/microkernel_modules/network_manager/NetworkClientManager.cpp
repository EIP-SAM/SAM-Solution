#include "NetworkClientManager.hpp"
#include "MainController.hpp"
#include <QByteArray>

#include <QDebug>

const QString NetworkClientManager::_ENCRYPTION_CERTIFICATE_FILE = "server.crt";
const QSsl::SslProtocol NetworkClientManager::_DEFAULT_PROTOCOL = QSsl::TlsV1_2;

//
// Constructor
// Add signal to readReady.
//
NetworkClientManager::NetworkClientManager()
    : ANetworkManager(false), _socket(this)
{
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(&_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

//
// Destructor
//
NetworkClientManager::~NetworkClientManager()
{
    disconnect();
    delete _inputBuffer;
    delete _outputBuffer;
}

//
// Entry point of the functionality
// Start the network client
//
void NetworkClientManager::_run()
{
    qDebug() << Q_FUNC_INFO;
    startConnection("localhost", 42042);
}

//
// Connection to server and send a first message
//
void NetworkClientManager::startConnection(const QString &ip, quint16 port)
{
    _socket.setProtocol(_DEFAULT_PROTOCOL);
    _socket.addCaCertificates(_ENCRYPTION_CERTIFICATE_FILE);
    _socket.connectToHostEncrypted(ip, port);
    if (!_socket.waitForEncrypted(15000))
        qDebug() << "Error:" << _socket.errorString();
}

//
// Disconnect socket from host
//
void NetworkClientManager::disconnect()
{
    _socket.close();
}

//
// Set peer input buffer pointer
//
void NetworkClientManager::_setPeerInputBuffer(InstructionBuffer *buffer, quint64 peerId)
{
    (void)peerId;
    _inputBuffer = buffer;
}

//
// Get peer input buffer pointer
//
InstructionBuffer *NetworkClientManager::_getPeerInputBuffer(quint64 peerId) const
{
    (void)peerId;
    return _inputBuffer;
}

//
// Slot activated in the case of a non threaded functionality
// This functionality runs on the main thread in the Qt event loop
// Handle what to do when a new instruction (from the instruction
// bus) is received
//
void NetworkClientManager::onInstructionPushed()
{
    InstructionBuffer *instruction = static_cast<InstructionBuffer *>(_popInstruction());

    qDebug() << Q_FUNC_INFO;
    if (!_instructionPushedIsValid(instruction))
    {
        delete instruction;
        return ;
    }
    if (!_write(instruction, _socket))
        disconnect();
    delete instruction;
}

//
// Read message from the server and push an AInstruction
// to the instruction bus
//
void NetworkClientManager::onReadyRead()
{
    InstructionBuffer *instruction = _inputBuffer;
    qint64 bytesAvailable = _socket.bytesAvailable();

    qDebug() << Q_FUNC_INFO;
    while (bytesAvailable > 0)
    {
        if (!instruction)
        {
            instruction = new InstructionBuffer();
            instruction->setPeerId(1);
            instruction->setLocalTransmitter(this);
            _inputBuffer = instruction;
        }
        if (!_read(instruction, _socket, bytesAvailable))
        {
            disconnect();
            delete _inputBuffer;
            _inputBuffer = NULL;
            return ;
        }
        _finalizeReceivedInstruction(instruction, 1);
    }
}

//
// Handle QSslSocket disconnected signal
//
void NetworkClientManager::onDisconnected()
{
    qDebug() << "Disconnected from host";
}

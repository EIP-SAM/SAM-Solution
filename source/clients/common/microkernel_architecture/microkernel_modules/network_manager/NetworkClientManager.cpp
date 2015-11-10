#include "NetworkClientManager.hpp"
#include "ANetworkInstruction.hpp"
#include "MainController.hpp"
#include <QByteArray>

#include <QDebug>

const QString NetworkClientManager::_ENCRYPTION_CERTIFICATE_FILE = "server.crt";
const QSsl::SslProtocol NetworkClientManager::_DEFAULT_PROTOCOL = QSsl::TlsV1_2;

//
// Add signal to readReady.
//
NetworkClientManager::NetworkClientManager()
    : AFunctionality(NETWORK_MANAGER, false), _socket(this)
{
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(&_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

NetworkClientManager::~NetworkClientManager()
{
    disconnect();
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
//
//
void NetworkClientManager::onInstructionPushed()
{
    ANetworkInstruction *instruction = static_cast<ANetworkInstruction *>(_popInstruction());
    qint64 writtenSize = 0, ret = 0;
    QByteArray buffer;

    qDebug() << Q_FUNC_INFO;
    if (!instruction)
    {
        qDebug() << "Error: Bad news, there is no instruction in the queue";
        return ;
    }
    buffer = instruction->getRawData();
    while (writtenSize != instruction->getRawData().size())
    {
        if ((ret = _socket.write(buffer, buffer.size())) == -1)
        {
            qDebug() << "Error: An error occured while trying to write";
            disconnect();
            break ;
        }
        else if (ret == 0)
        {
            qDebug() << "Warning: Trying to write too much data";
            break ;
        }
        writtenSize += ret;
        if (writtenSize < ret)
            buffer = buffer.left(ret);
    }
    delete instruction;
}

//
// Read message from the server and push an AInstruction
// to the instruction bus
//
void NetworkClientManager::onReadyRead()
{
    ANetworkInstruction *instruction = _inputBuffer;
    qint64 bytesAvailable = _socket.bytesAvailable(), readSize = -1, ret = -1;
    QByteArray buffer;

    qDebug() << Q_FUNC_INFO;

    while (bytesAvailable > 0)
    {
        if (!instruction)
        {
            instruction = new ANetworkInstruction();
            instruction->setLocalTransmitter(this);
            _inputBuffer = instruction;
        }
        if (bytesAvailable <= instruction->getNextReadSize())
            readSize = bytesAvailable;
        else if (bytesAvailable > instruction->getNextReadSize())
            readSize = instruction->getNextReadSize();
        buffer.resize(readSize);
        if ((ret = _socket.read(buffer.data(), readSize)) == -1)
        {
            qDebug() << "Error: An error occured while trying to read";
            disconnect();
            return ;
        }
        else if (ret == 0)
        {
            qDebug() << "Warning: Trying to read more data than available";
            break ;
        }
        buffer.resize(ret);
        instruction->append(buffer);
        bytesAvailable -= ret;
        qDebug() << "Had read" << ret << "bytes";
        qDebug() << buffer;
        if (!instruction->getNextReadSize())
        {
            mainController->getInstructionBus().pushInstruction(instruction);
            _inputBuffer = NULL;
        }
    }
}

//
// Handle QSslSocket disconnected signal
//
void NetworkClientManager::onDisconnected()
{
    qDebug() << "Disconnected from host";
}

#include "NetworkClientManager.hpp"
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
//
//
void NetworkClientManager::onInstructionPushed()
{
    InstructionBuffer *instruction = static_cast<InstructionBuffer *>(_popInstruction());
    qint64 writtenSize = 0, ret = 0;
    QByteArray buffer;

    qDebug() << Q_FUNC_INFO;
    if (!instruction)
    {
        qDebug() << "Error: Bad news, there is no instruction in the queue";
        return ;
    }
    if (instruction->getTransmitterProgId() != mainController->getProgId())
    {
        qDebug() << "Error: Trying to send a malicious instruction; Instruction deleted";
        delete instruction;
        return ;
    }
    buffer = instruction->getData();
    while (writtenSize != instruction->getData().size())
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
    InstructionBuffer *instruction = _inputBuffer;
    qint64 bytesAvailable = _socket.bytesAvailable(), readSize = -1, ret = -1;
    QByteArray buffer;

    qDebug() << Q_FUNC_INFO;

    while (bytesAvailable > 0)
    {
        if (!instruction)
        {
            instruction = new InstructionBuffer();
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
        *instruction << buffer;
        bytesAvailable -= ret;
        qDebug() << "Had read" << ret << "bytes";
        qDebug() << buffer;
        if (!instruction->getNextReadSize())
        {
            if (instruction->finalizeFilling())
            {
                AFunctionality::eType fctType = mainController->getFunctionalityType(instruction->getFinalReceiver());

                if (mainController->getProgId() == instruction->getTransmitterProgId() ||
                    fctType == AFunctionality::MICROKERNEL || fctType == AFunctionality::INTERNAL)
                {
                    delete instruction;
                    qDebug() << "Error: Malicious instruction received; Instruction deleted";
                }
                else
                    mainController->pushInstruction(instruction);
            }
            else
            {
                delete instruction;
                qDebug() << "Error: Malformed instruction received; Instruction deleted";
            }
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

#include <QByteArray>
#include "NetworkClientManager.hpp"

#include <QDebug>

const QString NetworkClientManager::_ENCRYPTION_CERTIFICATE_FILE = "server.crt";
const QSsl::SslProtocol NetworkClientManager::_DEFAULT_PROTOCOL = QSsl::TlsV1_2;

//
// Add signal to readReady.
//

NetworkClientManager::NetworkClientManager(QObject *parent)
    : AFunctionality(parent), _client(this)
{
    connect(&_client, SIGNAL(readyRead()), this, SLOT(readMsg()));
    connect(&_client, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

NetworkClientManager::~NetworkClientManager()
{
}

//
// Entry point
// Start network client
//
void NetworkClientManager::run()
{
    qDebug() << Q_FUNC_INFO;
    startConnection("localhost", 42042);
}

//
// Connection to server and send a first message
//

void NetworkClientManager::startConnection(const QString &ip, quint16 port)
{
    _client.setProtocol(_DEFAULT_PROTOCOL);
    _client.addCaCertificates(_ENCRYPTION_CERTIFICATE_FILE);
    _client.connectToHostEncrypted(ip, port);
    if (_client.waitForEncrypted(3000))
    {
        qDebug() << "Client connected";
        AInstructionModel *instruction = new AInstructionModel;
        QByteArray *a = instruction->getByteArray();
        *a = "allo?";
        writeMsg(instruction);
    }
    else
    {
        qDebug() << "Error: " << _client.errorString();
    }
}

//
// Disconnect socket from host
//

void NetworkClientManager::disconnect()
{
    _client.close();
}

//
// Send to the server through the network message
//

bool NetworkClientManager::writeMsg(AInstructionModel *instruction)
{
    if (_client.write(*(instruction->getByteArray())) == -1)
    {
        qDebug() << "Error message not send";
        return (false);
    }
  return (true);
}

//
// Read message from the server and return AInstructionModel
//

QByteArray *NetworkClientManager::readMsg()
{
    QByteArray *byteArray = new QByteArray();

    *byteArray = _client.read(1024);
    qDebug() << "Incoming data :" << *byteArray;
    return (byteArray);
}

//
// Handle disconnected QSslSocket signal
//

void NetworkClientManager::onDisconnected()
{
    qDebug() << "Disconnected from host";
}

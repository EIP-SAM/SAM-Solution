#include "NetworkClient.hpp"
#include <QtNetwork>

//
// Construct network client
NetworkClient::NetworkClient(QObject *parent)
    : QObject(parent), _socket(this)
{
    qDebug() << Q_FUNC_INFO;
    connect(&_socket, SIGNAL(encrypted()),
            this, SLOT(onEncryptedState()));
    connect(&_socket, SIGNAL(disconnected()),
            this, SLOT(onDisconnectedState()));
    connect(&_socket, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(onEncryptionErrors(QList<QSslError>)));
}

//
// Destroy network client
NetworkClient::~NetworkClient()
{
    qDebug() << Q_FUNC_INFO;
    disconnect(&_socket, 0, 0, 0);
    disconnect(this, 0, 0, 0);
}

//
// Initialize and start client
bool NetworkClient::start(QSsl::SslProtocol protocol,
                          qintptr socketDescriptor,
                          const QSslKey &encryptionKey,
                          const QSslCertificate &encryptionCertificate)
{
    qDebug() << Q_FUNC_INFO;
    _socketDescriptor = socketDescriptor;
    _socket.setProtocol(protocol);
    _socket.addCaCertificate(encryptionCertificate);
    _socket.setLocalCertificate(encryptionCertificate);
    _socket.setPrivateKey(encryptionKey);
    _socket.setSocketOption(QAbstractSocket::KeepAliveOption, true);
    if (_socket.setSocketDescriptor(socketDescriptor))
        _socket.startServerEncryption();
    else
    {
        // Get details on error
        return (false);
    }
    qDebug() << "" << socketDescriptor
             << "TCP connexion successfuly established";
    return (true);
}

//
// Read data from socket when available
void NetworkClient::onReadyRead()
{
    QByteArray data = _socket.read(_socket.bytesAvailable());

    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << _socketDescriptor << "Incoming data: " << data;
    write(NULL); // temporary answer
}

//
// Write data on socket
void NetworkClient::write(void *instruction)
{
    QByteArray falseData("Hello foo world\n");
    qint64 size;

    (void)instruction;
    qDebug() << Q_FUNC_INFO;
    size = _socket.write(falseData.data(), falseData.size());
    qDebug() << "" << _socketDescriptor << "Bytes written :" << size;
}

//
// Handle encrypted state event
void NetworkClient::onEncryptedState()
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << _socketDescriptor
             << "QSsl::TlsV1_2 connexion successfuly established";
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

//
// Handle disconnected state event
void NetworkClient::onDisconnectedState()
{
    emit disconnected(_socket.socketDescriptor());
}

//
// Handle encryption errors event
void NetworkClient::onEncryptionErrors(QList<QSslError> errors)
{
    emit encryptionErrors(_socketDescriptor, errors);
}

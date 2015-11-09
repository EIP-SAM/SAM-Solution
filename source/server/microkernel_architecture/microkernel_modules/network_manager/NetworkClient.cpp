#include "NetworkClient.hpp"
#include <QtNetwork>

//
// Construct network client
//
NetworkClient::NetworkClient(quint64 clientId, QObject *parent)
    : QObject(parent), _socket(this), _clientId(clientId)
{
    qDebug() << Q_FUNC_INFO;
    connect(&_socket, SIGNAL(bytesWritten(qint64)),
            this, SLOT(onBytesWritten(qint64)));
    connect(&_socket, SIGNAL(encrypted()),
            this, SLOT(onEncryptedState()));
    connect(&_socket, SIGNAL(disconnected()),
            this, SLOT(onDisconnectedState()));
    connect(&_socket, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(onEncryptionErrors(QList<QSslError>)));
}

//
// Destroy network client
//
NetworkClient::~NetworkClient()
{
    qDebug() << Q_FUNC_INFO;
    disconnect(&_socket, 0, 0, 0);
    disconnect(this, 0, 0, 0);
}

//
// Initialize and start client
//
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
        qDebug() << "" << socketDescriptor
                 << "Error :" << _socket.errorString();
        return (false);
    }
    qDebug() << "" << socketDescriptor
             << "TCP connexion successfuly established";
    return (true);
}

//
//
//
void NetworkClient::close()
{
    qDebug() << Q_FUNC_INFO;
}

//
// Bytes available for reading
//
qint64 NetworkClient::bytesAvailable() const
{
    qDebug() << Q_FUNC_INFO;
    return (_socket.bytesAvailable());
}

//
// Bytes waiting to be written
//
qint64 NetworkClient::bytesToWrite() const
{
    qDebug() << Q_FUNC_INFO;
    return (_socket.bytesToWrite());
}

//
// Getter: return client socket descriptor
//
qintptr NetworkClient::getSocketDescriptor() const
{
    return _socketDescriptor;
}

//
// Getter: return client id
//
quint64 NetworkClient::getClientId() const
{
    return _clientId;
}

//
// Getter: return input buffer
//
ANetworkInstruction *NetworkClient::getInputBuffer() const
{
    return _inputBuffer;
}

//
// Getter: return output buffer
//
ANetworkInstruction *NetworkClient::getOutputBuffer() const
{
    return _outputBuffer;
}

//
// Setter: set input buffer
//
void NetworkClient::setInputBuffer(ANetworkInstruction *inputBuffer)
{
    _inputBuffer = inputBuffer;
}

//
// Setter: set output buffer
//
void NetworkClient::setOutputBuffer(ANetworkInstruction *outputBuffer)
{
    _outputBuffer = outputBuffer;
}

//
// Read data from socket when available
//
qint64 NetworkClient::read(QByteArray &data, qint64 size)
{
    qDebug() << Q_FUNC_INFO;
    return _socket.read(data.data(), size);
}

//
// Write data on socket
//
qint64 NetworkClient::write(const QByteArray &data, qint64 size)
{
    qDebug() << Q_FUNC_INFO;
    return _socket.write(data.constData(), size);
}

//
// Redirect QSslSocket signal to NetworkClient
//
void NetworkClient::onReadyRead()
{
    qDebug() << Q_FUNC_INFO;
    emit readyRead(_socketDescriptor);
}

//
// Redirect QSslSocket signal to NetworkClient
//
void NetworkClient::onBytesWritten(qint64 size)
{
    qDebug() << Q_FUNC_INFO;
    emit bytesWritten(_socketDescriptor, size);
}

//
// Handle encrypted state event
//
void NetworkClient::onEncryptedState()
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << _socketDescriptor
             << "QSsl::TlsV1_2 connexion successfuly established";
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

//
// Handle disconnected state event
//
void NetworkClient::onDisconnectedState()
{
    qDebug() << Q_FUNC_INFO;
    emit disconnected(_socket.socketDescriptor());
}

//
// Handle encryption errors event
//
void NetworkClient::onEncryptionErrors(QList<QSslError> errors)
{
    qDebug() << Q_FUNC_INFO;
    emit encryptionErrors(_socketDescriptor, errors);
}

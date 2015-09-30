#include "NetworkClient.hpp"
#include <QtNetwork>

NetworkClient::NetworkClient(QObject *parent)
    : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    connect(&_socket, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(newEncryptionError(QList<QSslError>)));
    connect(&_socket, SIGNAL(encrypted()),
            this, SLOT(isEncrypted()));
    connect(&_socket, SIGNAL(encrypted()),
            this, SLOT(read()));
    connect(&_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
}

NetworkClient::~NetworkClient()
{
    qDebug() << Q_FUNC_INFO;
    _socket.disconnectFromHost();
    _socket.waitForDisconnected();
}

bool NetworkClient::init(QSsl::SslProtocol protocol, qintptr socketDescriptor,
                         QSslKey &encryptionKey, QSslCertificate &encryptionCertificate)
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

void NetworkClient::read()
{
    QByteArray data = _socket.read(_socket.bytesAvailable());

    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << _socketDescriptor << "Incoming data: " << data;
    write(NULL); // temporary answer
}

void NetworkClient::write(void *instruction)
{
    QByteArray falseData("Hello foo world\n");
    qint64 size;

    (void)instruction;
    qDebug() << Q_FUNC_INFO;
    size = _socket.write(falseData.data(), falseData.size());
    qDebug() << "" << _socketDescriptor << "Bytes written :" << size;
}

void NetworkClient::isEncrypted()
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << _socketDescriptor
             << "QSsl::TlsV1_2 connexion successfuly established";
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(read()));
}

void NetworkClient::newEncryptionError(QList<QSslError> errors)
{
    QString errorStr = " ";

    qDebug() << Q_FUNC_INFO;
    qDebug() << _socketDescriptor;
    foreach (const QSslError &e, errors)
        errorStr.append(e.errorString()).append("\n");

    _socket.ignoreSslErrors(); // Be careful, not supposed to ignore them
    qDebug() << errorStr;
}

void NetworkClient::onStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << _socketDescriptor << socketState;
}

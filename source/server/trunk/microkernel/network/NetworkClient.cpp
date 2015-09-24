#include "NetworkClient.hpp"
#include <QtNetwork>

NetworkClient::NetworkClient(QObject *parent)
    : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
}

NetworkClient::~NetworkClient()
{
    qDebug() << Q_FUNC_INFO;
    _socket.disconnectFromHost();
    _socket.waitForDisconnected();
}

bool NetworkClient::init(QSsl::SslProtocol, qintptr socketDescriptor,
               QSslKey &encryptionKey, QSslCertificate &encryptionCertificate)
{
    QByteArray key;
    QByteArray cert;

    qDebug() << Q_FUNC_INFO;

    _socketDescriptor = socketDescriptor;
    _socket.setProtocol(QSsl::TlsV1_2);
    _socket.addCaCertificate(encryptionCertificate);
    _socket.setLocalCertificate(encryptionCertificate);
    _socket.setPrivateKey(encryptionKey);
    _socket.setSocketOption(QAbstractSocket::KeepAliveOption, true);

    qDebug() << _socketDescriptor;

    connect(&_socket, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(newEncryptionError(QList<QSslError>)));
    connect(&_socket, SIGNAL(encrypted()),
            this, SLOT(isEncrypted()));

    if (_socket.setSocketDescriptor(socketDescriptor))
    {
        connect(&_socket, SIGNAL(encrypted()), this, SLOT(readEvent()));
        _socket.startServerEncryption();
    }
    else
    {
        qDebug() << " Connection error";
        return (false);
    }

    qDebug() << " Connected!";
    return (true);
}

void NetworkClient::readEvent()
{
    QByteArray data = _socket.read(_socket.bytesAvailable());

    qDebug() << Q_FUNC_INFO;
    qDebug() << _socketDescriptor;
    qDebug() << " Incoming data: " << data;

    _socket.write("Wesh bien ou bien ?", sizeof("Wesh bien ou bien ?"));
}

void NetworkClient::isEncrypted()
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << _socketDescriptor << " Connection encrypted";
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(readEvent()));
}

void NetworkClient::newEncryptionError(QList<QSslError> errors)
{
    QString errorStr = " ";

    qDebug() << Q_FUNC_INFO;
    qDebug() << _socketDescriptor;
    foreach (const QSslError &e, errors)
        errorStr.append(e.errorString()).append("\n");

    _socket.ignoreSslErrors(); // Be careful
    qDebug() << errorStr;
}

#include "NetworkClient.hpp"
#include <QtNetwork>

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

NetworkClient::~NetworkClient()
{
    qDebug() << Q_FUNC_INFO;
    disconnect(&_socket, 0, 0, 0);
    disconnect(this, 0, 0, 0);
}

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

void NetworkClient::onReadyRead()
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

void NetworkClient::onEncryptedState()
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << _socketDescriptor
             << "QSsl::TlsV1_2 connexion successfuly established";
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void NetworkClient::onEncryptionErrors(QList<QSslError> errors)
{
    QString errorStr = " ";

    qDebug() << Q_FUNC_INFO;
    qDebug() << _socketDescriptor;
    foreach (const QSslError &e, errors)
        errorStr.append(e.errorString()).append("\n");

    _socket.ignoreSslErrors(); // Be careful, not supposed to ignore them
    qDebug() << errorStr;
}

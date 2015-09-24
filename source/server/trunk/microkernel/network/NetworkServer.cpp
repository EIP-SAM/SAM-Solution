#include "NetworkServer.hpp"
#include "NetworkClient.hpp"
#include <QByteArray>
#include "_QFile.hpp"

NetworkServer::NetworkServer(QObject *parent)
    : QTcpServer(parent)
{
    qDebug() << Q_FUNC_INFO;
}

NetworkServer::~NetworkServer()
{
    qDebug() << Q_FUNC_INFO;
    foreach (NetworkClient *client, _clientSockets)
    {
        delete client;
        _clientSockets.pop_front();
    }
}

bool NetworkServer::start(int portNumber)
{
    qDebug() << Q_FUNC_INFO;
    if (!_initEncryptionKey("server.key") ||
        !_initEncryptionCertificate("server.crt") ||
        !_listen(portNumber))
        return (false);
    return (true);
}

bool NetworkServer::_initEncryptionKey(const QString &file)
{
    const QByteArray *keyData = NULL;

    qDebug() << Q_FUNC_INFO;
    if (!(keyData = _QFile::readFile(file)))
    {
        delete keyData;
        return (false);
    }
    if (!(_encryptionKey = new QSslKey(*keyData, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, "server")))
    {
        qDebug() << " Error during encryption key interpretation";
        return (false);
    }
    delete keyData;
    return (true);
}

bool NetworkServer::_initEncryptionCertificate(const QString &file)
{
    const QByteArray *certificateData = NULL;

    qDebug() << Q_FUNC_INFO;
    if (!(certificateData = _QFile::readFile(file)))
    {
        delete certificateData;
        return (false);
    }
    if (!(_encryptionCertificate = new QSslCertificate(*certificateData)))
    {
        qDebug() << " Error during encryption certificate interpretation";
        return (false);
    }
    delete certificateData;
    return (true);
}

bool NetworkServer::_listen(int portNumber)
{
    _portNumber = portNumber;
    if (!listen(QHostAddress::Any, portNumber))
    {
        qDebug() << " Could not start server";
        return (false);
    }
    qDebug() << " Listening to port " << portNumber << "...";
    return (true);
}

void NetworkServer::incomingConnection(qintptr socketDescriptor)
{
    NetworkClient *client = new NetworkClient;

    qDebug() << Q_FUNC_INFO;
    qDebug() << " New client connected";

    _clientSockets.push_back(client);
    client->init(QSsl::TlsV1_2, socketDescriptor, *_encryptionKey, *_encryptionCertificate);
}

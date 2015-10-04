#include "NetworkServer.hpp"
#include "NetworkClient.hpp"
#include <QByteArray>
#include "_QFile.hpp"

const QString NetworkServer::_ENCRYPTION_KEY_FILE = "server.key";
const QString NetworkServer::_ENCRYPTION_CERTIFICATE_FILE = "server.crt";

NetworkServer::NetworkServer(QObject *parent)
    : QTcpServer(parent)
{
    qDebug() << Q_FUNC_INFO;
    if (!QMetaType::isRegistered(QMetaType::type("qintptr")))
        qRegisterMetaType<qintptr>("qintptr");
}

NetworkServer::~NetworkServer()
{
    qDebug() << Q_FUNC_INFO;
    foreach (NetworkClient *client, _clientSockets)
    {
        delete client;
        _clientSockets.pop_front();
    }
    delete _encryptionKey;
    delete _encryptionCertificate;
}

bool NetworkServer::start(quint16 portNumber)
{
    qDebug() << Q_FUNC_INFO;

    if (!_initEncryptionKey(_ENCRYPTION_KEY_FILE) ||
        !_initEncryptionCertificate(_ENCRYPTION_CERTIFICATE_FILE) ||
        !_listen(portNumber))
        return (false);
    return (true);
}

bool NetworkServer::_initEncryptionKey(const QString &file)
{
    const QByteArray *keyData = NULL;

    qDebug() << Q_FUNC_INFO;
    if (_encryptionKey)
        return (true);
    if (!(keyData = _QFile::readFile(file)))
        return (false);
    if (!(_encryptionKey = new QSslKey(*keyData, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, "server")))
    {
        qDebug() << " Error during encryption key interpretation";
        delete keyData;
        return (false);
    }
    delete keyData;
    return (true);
}

bool NetworkServer::_initEncryptionCertificate(const QString &file)
{
    const QByteArray *certificateData = NULL;

    qDebug() << Q_FUNC_INFO;
    if (_encryptionCertificate)
        return (true);
    if (!(certificateData = _QFile::readFile(file)))
        return (false);
    if (!(_encryptionCertificate = new QSslCertificate(*certificateData)))
    {
        qDebug() << " Error during encryption certificate interpretation";
        delete certificateData;
        return (false);
    }
    delete certificateData;
    return (true);
}

bool NetworkServer::_listen(quint16 portNumber)
{
    _portNumber = portNumber;
    if (!listen(QHostAddress::Any, portNumber))
    {
        qDebug() << " Could not start server";
        return (false);
    }
    qDebug() << " Listening to port" << portNumber << "...";
    return (true);
}

void NetworkServer::incomingConnection(qintptr socketDescriptor)
{
    NetworkClient *client = new NetworkClient(this);

    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << socketDescriptor << "New client connected";
    if (client->init(QSsl::TlsV1_2, socketDescriptor,
                     *_encryptionKey, *_encryptionCertificate))
        _clientSockets.push_back(client);
    else
    {
        qDebug() << "" << socketDescriptor << " Error during client initialization";
        delete client;
    }
}

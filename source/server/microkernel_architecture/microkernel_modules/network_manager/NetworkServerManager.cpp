#include "NetworkServerManager.hpp"
#include "NetworkClient.hpp"
#include <QByteArray>
#include "_QFile.hpp"
#include "ANetworkInstruction.hpp"

//
// NetworkServer static attributes assignation
//
const QString NetworkServerManager::_ENCRYPTION_KEY_FILE = "server.key";
const QString NetworkServerManager::_ENCRYPTION_CERTIFICATE_FILE = "server.crt";
const QSsl::SslProtocol NetworkServerManager::_DEFAULT_PROTOCOL = QSsl::TlsV1_2;

//
// Construct network server
//
NetworkServerManager::NetworkServerManager(QObject *parent)
    : AFunctionality(parent), _server(this)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<QList<QSslError> >("QList<QSslError>");
}

//
// Destroy network server
//
NetworkServerManager::~NetworkServerManager()
{
    qDebug() << Q_FUNC_INFO;
    for (auto socketDescriptor : _clientSockets.keys())
    {
        delete _clientSockets[socketDescriptor];
        _clientSockets.remove(socketDescriptor);
    }
    delete _encryptionKey;
    delete _encryptionCertificate;
}

//
// Entry point
//
void NetworkServerManager::run()
{
    connect(&_server, SIGNAL(hasIncomingConnection(qintptr)),
            this, SLOT(incomingConnection(qintptr)));
    start(42042);
}

//
// Initialize and start server
//
bool NetworkServerManager::start(quint16 portNumber)
{
    qDebug() << Q_FUNC_INFO;

    if (!QSslSocket::supportsSsl())
    {
        qDebug() << " Error SSL is not available on this machine";
        return (false);
    }
    qDebug() << QSslSocket::sslLibraryVersionString();
    if (!_initEncryptionKey(_ENCRYPTION_KEY_FILE) ||
        !_initEncryptionCertificate(_ENCRYPTION_CERTIFICATE_FILE) ||
        !_listen(portNumber))
        return (false);
    return (true);
}

//
// Initialize encryption key
//
bool NetworkServerManager::_initEncryptionKey(const QString &file)
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

//
// Initialize encryption certificate
//
bool NetworkServerManager::_initEncryptionCertificate(const QString &file)
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

//
// Make server listening on choosen port
//
bool NetworkServerManager::_listen(quint16 portNumber)
{
    _portNumber = portNumber;
    if (!_server.listen(QHostAddress::Any, portNumber))
    {
        qDebug() << " Could not start server";
        return (false);
    }
    qDebug() << " Listening to port" << portNumber << "...";
    return (true);
}

//
// Create and initialize a new client
//
void NetworkServerManager::incomingConnection(qintptr socketDescriptor)
{
    NetworkClient *client = new NetworkClient(this);

    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << socketDescriptor << "New client connected";
    if (client->start(_DEFAULT_PROTOCOL, socketDescriptor,
                      *_encryptionKey, *_encryptionCertificate))
    {
        _clientSockets[socketDescriptor] = client;
        connect(client, SIGNAL(readyRead(qintptr)),
                this, SLOT(onClientReadyRead(qintptr)), Qt::QueuedConnection);
        connect(client, SIGNAL(bytesWritten(qintptr, qint64)),
                this, SLOT(onClientBytesWritten(qintptr, qint64)), Qt::QueuedConnection);
        connect(client, SIGNAL(disconnected(qintptr)),
                this, SLOT(deleteClient(qintptr)), Qt::QueuedConnection);
        connect(client, SIGNAL(encryptionErrors(qintptr, QList<QSslError>)),
                this, SLOT(onClientEncryptionError(qintptr, QList<QSslError>)), Qt::QueuedConnection);
    }
    else
    {
        qDebug() << "" << socketDescriptor << " Error during client initialization";
        delete client;
    }
}

//
// Supposed to fill the client input buffer
//
void NetworkServerManager::onClientReadyRead(qintptr socketDescriptor)
{
    NetworkClient *client = _clientSockets[socketDescriptor];
    QByteArray data;
    qint64 size = -1;

    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << socketDescriptor
             << "Ready to read" << client->bytesAvailable() << "bytes";
    data.resize(client->bytesAvailable());
    size = client->read(data.data(), data.size());
    qDebug() << "" << socketDescriptor << "Had read" << size << "bytes. Incoming data :" << data;

    data = "Hello world\n";
    size = client->write(data.data(), data.size());
    qDebug() << "" << socketDescriptor << "Had put" << size << "bytes. Outcoming data :" << data;
}

//
// Supposed to handle the outcoming data
//
void NetworkServerManager::onClientBytesWritten(qintptr socketDescriptor, qint64 size)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << socketDescriptor
             << "Written bytes :" << size;
}

//
// Delete a disconnected client
//
void NetworkServerManager::deleteClient(qintptr socketDescriptor)
{
    NetworkClient *client = _clientSockets[socketDescriptor];

    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << socketDescriptor << "Client disconnected";
    _server.disconnect(client, 0, 0, 0);
    _clientSockets.remove(socketDescriptor);
    delete client;
    qDebug() << "" << socketDescriptor << "Client deleted";
}

//
// Print client encryption errors
//
void NetworkServerManager::onClientEncryptionError(qintptr socketDescriptor, QList<QSslError> errors)
{
    QString errorStr = " ";

    qDebug() << Q_FUNC_INFO;
    qDebug() << "" << socketDescriptor << "Encryption error";
    for (auto e : errors)
        errorStr.append(e.errorString()).append("\n");
    qDebug() << errorStr;
}

//
// Slot activated in the case of a non threaded functionality
// This functionality runs on the main thread in the Qt event loop
// Handle what to do when a new instruction (from the instruction
// bus) is received
//
void NetworkServerManager::onInstructionPushed()
{
    AInstruction *instruction = NULL;

    qDebug() << Q_FUNC_INFO;
    instruction = _popInstruction();
    (void)instruction;
}

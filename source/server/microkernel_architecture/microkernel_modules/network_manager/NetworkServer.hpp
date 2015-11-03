#ifndef NETWORK_SERVER_HPP_
# define NETWORK_SERVER_HPP_

# include <QSslKey>
# include <QSslCertificate>
# include <QSslError>
# include <QMap>
# include "_QTcpServer.hpp"
# include "AFunctionality.hpp"

class NetworkClient;
class AInstructionModel;

class NetworkServer : public AFunctionality
{
    Q_OBJECT

public:
    explicit NetworkServer(QObject *parent = 0);
    ~NetworkServer();

private:
    static const QString _ENCRYPTION_KEY_FILE;
    static const QString _ENCRYPTION_CERTIFICATE_FILE;
    static const QSsl::SslProtocol _DEFAULT_PROTOCOL;

    _QTcpServer _server;
    quint16 _portNumber;
    QSslKey *_encryptionKey = NULL;
    QSslCertificate *_encryptionCertificate = NULL;
    QMap<qintptr, NetworkClient *> _clientSockets;

public:
    bool start(quint16 portNumber);

private:
    bool _initEncryptionKey(const QString &file);
    bool _initEncryptionCertificate(const QString &file);
    bool _listen(quint16 portNumber);

private slots:
    void incomingConnection(qintptr socketDescriptor);
    void onClientReadyRead(qintptr socketDescriptor);
    void pushInstruction(AInstructionModel *instruction);
    void onClientBytesWritten(qintptr socketDescriptor, qint64 size);
    void deleteClient(qintptr socketDescriptor);
    void onClientEncryptionError(qintptr socketDescriptor, QList<QSslError> errors);

protected slots:
    virtual void run();
};

#endif // !NETWORK_SERVER_HPP_

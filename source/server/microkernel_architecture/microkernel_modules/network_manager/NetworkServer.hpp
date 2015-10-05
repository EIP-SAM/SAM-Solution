#ifndef NETWORKSERVER_HPP_
# define NETWORKSERVER_HPP_

# include <QTcpServer>
# include <QSslKey>
# include <QSslCertificate>
# include <QSslError>
# include <QMap>

class NetworkClient;

class NetworkServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit NetworkServer(QObject *parent = 0);
    ~NetworkServer();

private:
    static const QString _ENCRYPTION_KEY_FILE;
    static const QString _ENCRYPTION_CERTIFICATE_FILE;
    static const QSsl::SslProtocol _DEFAULT_PROTOCOL;

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

protected:
    void incomingConnection(qintptr socketDescriptor);

signals:

public slots:
    void deleteClient(qintptr socketDescriptor);
    void onClientEncryptionError(qintptr socketDescriptor, QList<QSslError> errors);
};

#endif // !NETWORKSERVER_HPP_

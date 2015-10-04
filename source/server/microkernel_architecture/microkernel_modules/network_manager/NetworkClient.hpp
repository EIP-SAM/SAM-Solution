#ifndef     NETWORKCLIENT_HPP
# define    NETWORKCLIENT_HPP

# include <QSslSocket>

class NetworkClient : public QObject
{
    Q_OBJECT

private:
    QSslSocket _socket;
    qintptr _socketDescriptor = -1;

public:
    explicit NetworkClient(QObject *parent = 0);
    ~NetworkClient();

    bool start(QSsl::SslProtocol protocol,
               qintptr socketDescriptor,
               const QSslKey &encryptionKey,
               const QSslCertificate &encryptionCertificate);
    void close();

signals:

public slots:
    void write(void *instruction);
    void onReadyRead();
    void onEncryptedState();
    void onDisconnectedState();
    void onEncryptionErrors(QList<QSslError> errors);
};

#endif      // NETWORKCLIENT_HPP

#ifndef     NETWORKCLIENT_HPP
# define    NETWORKCLIENT_HPP

# include <QSslSocket>

class NetworkClient : public QObject
{
    Q_OBJECT

private:
    QSslSocket _socket;
    qintptr _socketDescriptor;

public:
    explicit NetworkClient(QObject *parent = 0);
    ~NetworkClient();

    bool init(QSsl::SslProtocol protocol, qintptr socketDescriptor,
              QSslKey &encryptionKey, QSslCertificate &encryptionCertificate);

signals:
    void stateChanged(QAbstractSocket::SocketState);

public slots:
    void read();
    void write(void *instruction);
    void isEncrypted();
    void newEncryptionError(QList<QSslError> errors);
    void onStateChanged(QAbstractSocket::SocketState socketState);
};

#endif      // NETWORKCLIENT_HPP

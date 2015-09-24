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

    bool init(QSsl::SslProtocol, qintptr socketDescriptor,
              QSslKey &encryptionKey, QSslCertificate &encryptionCertificate);

signals:

public slots:
    void readEvent();
    void isEncrypted();
    void newEncryptionError(QList<QSslError> errors);
};

#endif      // NETWORKCLIENT_HPP

#ifndef NETWORKCLIENT_HPP_
# define NETWORKCLIENT_HPP_

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
    qint64 bytesAvailable() const;
    qint64 bytesToWrite() const;

signals:
    void readyRead(qintptr socketDescriptor);
    void bytesWritten(qintptr socketDescriptor, qint64 size);
    void disconnected(qintptr socketDescriptor);
    void encryptionErrors(qintptr socketDescriptor, QList<QSslError> errors);

public slots:
    qint64 write(const char *data, qint64 size);
    qint64 read(char *data, qint64 size);
    void onReadyRead();
    void onBytesWritten(qint64 size);
    void onEncryptedState();
    void onDisconnectedState();
    void onEncryptionErrors(QList<QSslError> errors);
};

#endif // NETWORKCLIENT_HPP_

#ifndef NETWORK_CLIENT_HPP_
# define NETWORK_CLIENT_HPP_

# include <QSslSocket>
# include "ANetworkInstruction.hpp"

class NetworkClient : public QObject
{
    Q_OBJECT

private:
    QSslSocket _socket;
    qintptr _socketDescriptor = -1;
    quint64 _clientId = 0;
    ANetworkInstruction *_inputBuffer = NULL;
    ANetworkInstruction *_outputBuffer = NULL;

public:
    NetworkClient(quint64 clientId, QObject *parent = 0);
    ~NetworkClient();

    bool start(QSsl::SslProtocol protocol,
               qintptr socketDescriptor,
               const QSslKey &encryptionKey,
               const QSslCertificate &encryptionCertificate);
    void close();
    qint64 bytesAvailable() const;
    qint64 bytesToWrite() const;
    qintptr getSocketDescriptor() const;
    quint64 getClientId() const;
    ANetworkInstruction *getInputBuffer() const;
    ANetworkInstruction *getOutputBuffer() const;

    void setInputBuffer(ANetworkInstruction *);
    void setOutputBuffer(ANetworkInstruction *);

signals:
    void readyRead(qintptr socketDescriptor);
    void bytesWritten(qintptr socketDescriptor, qint64 size);
    void disconnected(qintptr socketDescriptor);
    void encryptionErrors(qintptr socketDescriptor, QList<QSslError> errors);

public slots:
    qint64 write(const QByteArray &data, qint64 size);
    qint64 read(QByteArray &data, qint64 size);
    void onReadyRead();
    void onBytesWritten(qint64 size);
    void onEncryptedState();
    void onDisconnectedState();
    void onEncryptionErrors(QList<QSslError> errors);
};

#endif // NETWORK_CLIENT_HPP_

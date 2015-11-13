#ifndef NETWORK_CLIENT_HPP_
# define NETWORK_CLIENT_HPP_

# include <QSslSocket>
# include "InstructionBuffer.hpp"

class NetworkClient : public QObject
{
    Q_OBJECT

private:
    QSslSocket _socket;
    qintptr _socketDescriptor = -1;
    quint64 _clientId = 0;
    InstructionBuffer *_inputBuffer = NULL;
    InstructionBuffer *_outputBuffer = NULL;

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
    InstructionBuffer *getInputBuffer() const;
    InstructionBuffer *getOutputBuffer() const;

    void setInputBuffer(InstructionBuffer *);
    void setOutputBuffer(InstructionBuffer *);
    qint64 write(const QByteArray &data, qint64 size);
    qint64 read(QByteArray &data, qint64 size);

private:
    bool _bindSocketSignalsToSlots();

signals:
    void readyRead(qintptr socketDescriptor);
    void bytesWritten(qintptr socketDescriptor, qint64 size);
    void disconnected(qintptr socketDescriptor);
    void encryptionErrors(qintptr socketDescriptor, QList<QSslError> errors);

private slots:
    void _onReadyRead();
    void _onBytesWritten(qint64 size);
    void _onEncryptedState();
    void _onDisconnectedState();
    void _onEncryptionErrors(QList<QSslError> errors);
};

#endif // NETWORK_CLIENT_HPP_

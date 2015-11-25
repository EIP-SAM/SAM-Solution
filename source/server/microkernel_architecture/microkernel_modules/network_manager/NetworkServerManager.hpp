#ifndef NETWORK_SERVER_MANAGER_HPP_
# define NETWORK_SERVER_MANAGER_HPP_

# include "ANetworkManager.hpp"
# include "_QTcpServer.hpp"
# include <QSslCertificate>
# include <QSslKey>
# include <QSslError>
# include <QMap>

class NetworkClient;

class NetworkServerManager : public ANetworkManager
{
    Q_OBJECT

public:
    NetworkServerManager(quint16 port);
    ~NetworkServerManager();

private:
    static const QString _ENCRYPTION_KEY_FILE;
    static const QString _ENCRYPTION_CERTIFICATE_FILE;
    static const QSsl::SslProtocol _DEFAULT_PROTOCOL;

    const quint16 _port;

    _QTcpServer _server;
    quint16 _portNumber;
    QSslKey *_encryptionKey = NULL;
    QSslCertificate *_encryptionCertificate = NULL;
    QMap<qintptr, NetworkClient *> _clientSockets;
    QMap<quint64, NetworkClient *> _clientIds;

public:
    bool start();

protected:
    virtual void _setPeerInputBuffer(InstructionBuffer *, quint64);
    virtual InstructionBuffer *_getPeerInputBuffer(quint64) const;

private:
    bool _initEncryptionKey(const QString &file);
    bool _initEncryptionCertificate(const QString &file);
    bool _listen(quint16 portNumber);
    void _deleteClient(NetworkClient *);
    bool _bindClientSignalsToSlots(NetworkClient *client);

private slots:
    void _incomingConnection(qintptr socketDescriptor);
    void _onClientReadyRead(qintptr socketDescriptor);
    void _onClientBytesWritten(qintptr socketDescriptor, qint64 size);
    void _deleteClient(qintptr socketDescriptor);
    void _onClientEncryptionError(qintptr socketDescriptor, QList<QSslError> errors);

protected slots:
    virtual void _run();

public slots:
    virtual void onInstructionPushed();
};

#endif // !NETWORK_SERVER_MANAGER_HPP_

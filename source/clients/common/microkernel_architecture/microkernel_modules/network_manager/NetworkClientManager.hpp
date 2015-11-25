#ifndef NETWORK_CLIENT_MANAGER_HPP_
# define NETWORK_CLIENT_MANAGER_HPP_

# include <QSslSocket>
# include "InstructionBuffer.hpp"
# include "ANetworkManager.hpp"

class NetworkClientManager : public ANetworkManager
{
    Q_OBJECT

private:
    static const QString _ENCRYPTION_CERTIFICATE_FILE;
    static const QSsl::SslProtocol _DEFAULT_PROTOCOL;

    const QString _hostname;
    const quint16 _port;

    QSslSocket _socket;
    InstructionBuffer *_inputBuffer = NULL;
    InstructionBuffer *_outputBuffer = NULL;

public:
    NetworkClientManager(const QString& hostname, quint16 port);
    virtual ~NetworkClientManager();

    void startConnection();
    void disconnect();

protected:
    virtual void _setPeerInputBuffer(InstructionBuffer *, quint64);
    virtual InstructionBuffer *_getPeerInputBuffer(quint64) const;

public slots:
    virtual void onInstructionPushed();

protected slots:
    virtual void _run();

private slots:
    void onReadyRead();
    void onDisconnected();
};

#endif // !NETWORK_CLIENT_MANAGER_HPP_

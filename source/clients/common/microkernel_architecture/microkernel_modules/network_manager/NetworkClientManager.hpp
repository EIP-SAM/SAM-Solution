#ifndef NETWORK_CLIENT_MANAGER_HPP_
# define NETWORK_CLIENT_MANAGER_HPP_

# include <QSslSocket>
# include "ANetworkInstruction.hpp"
# include "AFunctionality.hpp"

class NetworkClientManager : public AFunctionality
{
    Q_OBJECT

private:
    static const QString _ENCRYPTION_CERTIFICATE_FILE;
    static const QSsl::SslProtocol _DEFAULT_PROTOCOL;

    QSslSocket _socket;
    ANetworkInstruction *_inputBuffer = NULL;
    ANetworkInstruction *_outputBuffer = NULL;

public:
    NetworkClientManager();
    virtual ~NetworkClientManager();

    void startConnection(const QString &ip, quint16 port);
    void disconnect();

public slots:
    virtual void run();
    virtual void onInstructionPushed();

private slots:
    void onReadyRead();
    void onDisconnected();
};

#endif // !NETWORK_CLIENT_MANAGER_HPP_

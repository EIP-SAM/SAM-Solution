#ifndef NETWORK_CLIENT_MANAGER_HPP_
# define NETWORK_CLIENT_MANAGER_HPP_

#include <QSslSocket>
#include "INetworkClientManager.hpp"

class NetworkClientManager : public QObject, public INetworkClientManager
{
  Q_OBJECT

private:
    static const QString _ENCRYPTION_CERTIFICATE_FILE;
    static const QSsl::SslProtocol _DEFAULT_PROTOCOL;

    QSslSocket _client;

public:
  explicit NetworkClientManager(QObject *parent = 0);
  ~NetworkClientManager();

  void startConnection(const QString &ip, quint16 port);
  void disconnect();

public slots:
  bool writeMsg(AInstructionModel *instruction);
  QByteArray *readMsg();
};

#endif // !NETWORK_CLIENT_MANAGER_HPP_

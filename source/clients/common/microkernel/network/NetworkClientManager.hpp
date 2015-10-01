#ifndef		NETWORK_CLIENT_MANAGER_HPP_
# define	NETWORK_CLIENT_MANAGER_HPP_

#include	<QSslSocket>
#include	<QObject>
#include	"INetworkClientManager.hpp"

class		NetworkClientManager : public QObject, public INetworkClientManager
{
  Q_OBJECT
public:
  NetworkClientManager();
  ~NetworkClientManager();

  void		startConnection(QString ip, quint16 port);
  void		disconnect();

public slots:
  bool		writeMsg(AInstructionModel *instruction);
  QByteArray	*readMsg();

private:
  QSslSocket	_client;
};

#endif		/* !NETWORK_CLIENT_MANAGER_HPP_ */

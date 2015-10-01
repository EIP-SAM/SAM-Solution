#ifndef			INETWORK_CLIENT_MANAGER_HPP_
# define		INETWORK_CLIENT_MANAGER_HPP_

#include		"AInstructionModel.hpp"

class			INetworkClientManager
{
public:
  virtual void		startConnection(QString ip, quint16 port) = 0;
  virtual bool		writeMsg(AInstructionModel *instruction) = 0;
  virtual QByteArray	*readMsg() = 0;
  virtual void		disconnect() = 0;
};

#endif			/* !INETWORK_CLIENT_MANAGER_HPP_ */

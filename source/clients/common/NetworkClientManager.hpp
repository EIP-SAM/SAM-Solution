#include	<QSslSocket>
#include	<QObject>
#include	"INetworkClientManager.hpp"

class		NetworkClientManager : public QObject, public INetworkClientManager
{
  Q_OBJECT
public:
  NetworkClientManager();
  ~NetworkClientManager();

  void		connected();
  std::string	receive();
  void		disconnect();

public slots:
    bool	send();

private:
  QSslSocket	client;
};

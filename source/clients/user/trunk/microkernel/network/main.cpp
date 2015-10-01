#include	<QApplication>
#include	"NetworkClientManager.hpp"

int		main(int ac, char **av)
{
  QApplication app(ac, av);

  NetworkClientManager *ncm = new NetworkClientManager();

  ncm->startConnection("127.0.0.1", 42042);
  return app.exec();
}

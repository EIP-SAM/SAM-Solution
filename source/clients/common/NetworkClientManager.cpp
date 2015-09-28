#include	<stdio.h>
#include	<iostream>
#include	"NetworkClientManager.hpp"
#include	<QApplication>

NetworkClientManager::NetworkClientManager()
{
  connect(&client, SIGNAL(encrypted()), this, SLOT(sendtest()));
}

NetworkClientManager::~NetworkClientManager()
{
}

void		NetworkClientManager::connected()
{
  // TODO
  // remove address and port
  QString address = "127.0.0.1";
  quint16 port = 42042;

  client.setProtocol(QSsl::TlsV1_2);
  client.addCaCertificates("server.crt");
  client.connectToHostEncrypted(address, port);
  if (client.waitForEncrypted(3000))
    {
      qDebug("connected");
    }
  else
    {
      qDebug("Error");
      qDebug() << client.errorString();
    }
}

bool		NetworkClientManager::sendtest()
{
  qDebug() << "Send a msg";
  client.write("HELLO", 5);
  return (true);
}

std::string	NetworkClientManager:: receive()
{
  return ("FUCK");
}

void		NetworkClientManager::disconnect()
{
}

int main(int argc, char **argv) {

  QApplication app(argc, argv);

  NetworkClientManager *ncm = new NetworkClientManager();

  ncm->connected();
  return app.exec();
}

#include	<stdio.h>
#include	<iostream>
#include	"NetworkClientManager.hpp"

NetworkClientManager::NetworkClientManager()
{
  connect(&client, SIGNAL(encrypted()), this, SLOT(send()));
}

NetworkClientManager::~NetworkClientManager()
{
}

void		NetworkClientManager::connected()
{
  // TODO
  // remove address and port
  QString address;
  quint16 port;

  client.setProtocol(QSsl::TlsV1_2);
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

bool		NetworkClientManager::send()
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

int main() {
  NetworkClientManager *ncm = new NetworkClientManager();

  ncm->connected();
  return 0;
}

#include	<stdio.h>
#include	<iostream>
#include	<QApplication>
#include	<QDataStream>
#include	<QByteArray>
#include	"NetworkClientManager.hpp"

NetworkClientManager::NetworkClientManager()
{
  connect(&client, SIGNAL(readyRead()), this, SLOT(readMsg()));
}

NetworkClientManager::~NetworkClientManager()
{
}

void		NetworkClientManager::startConnection(QString ip, quint16 port)
{
  client.setProtocol(QSsl::TlsV1_2);
  client.addCaCertificates("server.crt");
  client.connectToHostEncrypted(ip, port);
  if (client.waitForEncrypted(3000))
    {
      qDebug() << "Client connected";
      writeMsg("HELLO my name is claire");
    }
  else
    {
      qDebug() << "Error: " << client.errorString();
    }
}

bool		NetworkClientManager::writeMsg(const char *msg)
{
  quint64	sizeMsg = strlen(msg);

  AInstruction *instruction = new AInstruction();
  qDebug() << "IN";

  if (client.write(msg, sizeMsg) == -1)
    {
      qDebug() << "Error message not send";
      return (false);
    }
  return (true);
}

std::string	NetworkClientManager::readMsg()
{
  char		buffer[1024];

  if (client.read(buffer, 1024) == -1)
    {
      qDebug() << "Error can not ready";
    }
  qDebug() << "buffer: " << buffer;
  return ("");
}

void		NetworkClientManager::disconnect()
{
}

int main(int argc, char **argv) {

  QApplication app(argc, argv);

  NetworkClientManager *ncm = new NetworkClientManager();

  ncm->startConnection("127.0.0.1", 42042);
  return app.exec();
}

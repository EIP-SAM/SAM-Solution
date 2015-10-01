#include		<stdio.h>
#include		<iostream>
#include		<QApplication>
#include		<QDataStream>
#include		<QByteArray>
#include		"NetworkClientManager.hpp"

//
// Add signal to readReady.
//

NetworkClientManager::NetworkClientManager()
{
  connect(&client, SIGNAL(readyRead()), this, SLOT(readMsg()));
}

NetworkClientManager::~NetworkClientManager()
{
}

//
// Connection to server and send a first message
//

void			NetworkClientManager::startConnection(QString ip, quint16 port)
{
  client.setProtocol(QSsl::TlsV1_2);
  client.addCaCertificates("server.crt");
  client.connectToHostEncrypted(ip, port);
  if (client.waitForEncrypted(3000))
    {
      qDebug() << "Client connected";
      AInstructionModel *instruction = new AInstructionModel();
      writeMsg(instruction);
    }
  else
    {
      qDebug() << "Error: " << client.errorString();
    }
}

//
// Send to the server through the network message
//

bool			NetworkClientManager::writeMsg(AInstructionModel *instruction)
{
  if (client.write(*(instruction->getByteArray())) == -1)
    {
      qDebug() << "Error message not send";
      return (false);
    }
  return (true);
}

//
// Read message from the server and return AInstructionModel
//

QByteArray	*NetworkClientManager::readMsg()
{
  QByteArray		*byteArray = new QByteArray();

  *byteArray = client.read(1024);
  qDebug() << "buffer: " << *byteArray;
  return (byteArray);
}

void			NetworkClientManager::disconnect()
{
}

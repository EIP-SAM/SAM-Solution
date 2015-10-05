#include <QByteArray>
#include "NetworkClientManager.hpp"

const QString NetworkClientManager::_ENCRYPTION_CERTIFICATE_FILE = "server.crt";
const QSsl::SslProtocol NetworkClientManager::_DEFAULT_PROTOCOL = QSsl::TlsV1_2;

//
// Add signal to readReady.
//

NetworkClientManager::NetworkClientManager(QObject *parent)
    : QObject(parent), _client(this)
{
  connect(&_client, SIGNAL(readyRead()), this, SLOT(readMsg()));
}

NetworkClientManager::~NetworkClientManager()
{
}

//
// Connection to server and send a first message
//

void NetworkClientManager::startConnection(const QString &ip, quint16 port)
{
  _client.setProtocol(_DEFAULT_PROTOCOL);
  _client.addCaCertificates(_ENCRYPTION_CERTIFICATE_FILE);
  _client.connectToHostEncrypted(ip, port);
  if (_client.waitForEncrypted(3000))
    {
      qDebug() << "Client connected";
      AInstructionModel *instruction = new AInstructionModel;
      QByteArray *a = instruction->getByteArray();
      *a = "allo?";
      writeMsg(instruction);
    }
  else
    {
      qDebug() << "Error: " << _client.errorString();
    }
}

//
// Send to the server through the network message
//

bool NetworkClientManager::writeMsg(AInstructionModel *instruction)
{
  if (_client.write(*(instruction->getByteArray())) == -1)
    {
      qDebug() << "Error message not send";
      return (false);
    }
  return (true);
}

//
// Read message from the server and return AInstructionModel
//

QByteArray *NetworkClientManager::readMsg()
{
  QByteArray *byteArray = new QByteArray();

  *byteArray = _client.read(1024);
  qDebug() << "Incoming data :" << *byteArray;
  return (byteArray);
}

void NetworkClientManager::disconnect()
{
}

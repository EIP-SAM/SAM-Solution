#include "NetworkServer.hpp"

NetworkServer::NetworkServer(QObject *parent)
    : QTcpServer(parent)
{
}

NetworkServer::~NetworkServer()
{
}

bool NetworkServer::start(int portNumber)
{
    return (true);
}

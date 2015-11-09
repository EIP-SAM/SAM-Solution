#include "_QTcpServer.hpp"

#include <QDebug>

_QTcpServer::_QTcpServer(QObject *parent)
    : QTcpServer(parent)
{
    qRegisterMetaType<qintptr>("qintptr");
}

_QTcpServer::~_QTcpServer()
{
}

void _QTcpServer::incomingConnection(qintptr socketDescriptor)
{
    emit hasIncomingConnection(socketDescriptor);
}

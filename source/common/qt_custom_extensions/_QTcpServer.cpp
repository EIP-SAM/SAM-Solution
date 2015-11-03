#include "_QTcpServer.hpp"

#include <QDebug>

_QTcpServer::_QTcpServer(QObject *parent)
    : QTcpServer(parent)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<qintptr>("qintptr");
}

_QTcpServer::~_QTcpServer()
{
}

void _QTcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << Q_FUNC_INFO;
    emit hasIncomingConnection(socketDescriptor);
}

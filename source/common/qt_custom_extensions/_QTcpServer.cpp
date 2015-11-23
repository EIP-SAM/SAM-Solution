#include "_QTcpServer.hpp"

//
// Constructor
//
_QTcpServer::_QTcpServer(QObject *parent)
    : QTcpServer(parent)
{
    qRegisterMetaType<qintptr>("qintptr");
}

//
// Destructor
//
_QTcpServer::~_QTcpServer()
{
}

//
// `incomingConnection()` emit its own signal `hasIncomingConnection()`
//
void _QTcpServer::incomingConnection(qintptr socketDescriptor)
{
    emit hasIncomingConnection(socketDescriptor);
}

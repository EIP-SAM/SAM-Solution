#ifndef _QTCP_SERVER_H
# define _QTCP_SERVER_H

# include <QTcpServer>

class _QTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit _QTcpServer(QObject *parent = 0);
    ~_QTcpServer();

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

signals:
    void hasIncomingConnection(qintptr socketDescriptor);
};

#endif // _QTCPSERVER_H

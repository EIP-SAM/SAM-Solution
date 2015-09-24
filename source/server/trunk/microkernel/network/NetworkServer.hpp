#ifndef     NETWORKSERVER_HPP
# define    NETWORKSERVER_HPP

# include <QTcpServer>

class NetworkServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit NetworkServer(QObject *parent = 0);
    ~NetworkServer();

    bool start(int portNumber);

};

#endif      // NETWORKSERVER_HPP

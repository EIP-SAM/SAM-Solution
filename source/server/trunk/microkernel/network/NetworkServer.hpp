#ifndef     NETWORKSERVER_HPP
# define    NETWORKSERVER_HPP

# include <QTcpServer>
# include <QSslKey>
# include <QSslCertificate>
# include <QList>

class NetworkClient;

class NetworkServer : public QTcpServer
{
    Q_OBJECT

private:
    int _portNumber;
    QSslKey *_encryptionKey = NULL;
    QSslCertificate *_encryptionCertificate = NULL;
    QList<NetworkClient *> _clientSockets;

public:
    explicit NetworkServer(QObject *parent = 0);
    ~NetworkServer();

    bool start(int portNumber);

private:
    bool _initEncryptionKey(const QString &file);
    bool _initEncryptionCertificate(const QString &file);
    bool _listen(int portNumber);

signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif      // NETWORKSERVER_HPP

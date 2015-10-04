#ifndef     MAINCONTROLLER_HPP
# define    MAINCONTROLLER_HPP

# include <QCoreApplication>

class NetworkServer;

class MainController : QObject
{
    Q_OBJECT

private:
    QCoreApplication _qtCore;
    NetworkServer *_network = NULL;

public:
    MainController(int, char **);
    ~MainController();

    int run();

private:
    bool _initNetwork();
};

#endif      // MAINCONTROLLER_HPP

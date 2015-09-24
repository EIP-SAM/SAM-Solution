#ifndef     MAINCONTROLLER_H
# define    MAINCONTROLLER_H

# include <QCoreApplication>

class NetworkServer;

class MainController
{
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

#endif      // MAINCONTROLLER_H

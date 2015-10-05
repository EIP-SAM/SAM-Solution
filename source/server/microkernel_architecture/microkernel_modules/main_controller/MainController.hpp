#ifndef MAINCONTROLLER_HPP_
# define MAINCONTROLLER_HPP_

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

#endif // !MAINCONTROLLER_HPP_

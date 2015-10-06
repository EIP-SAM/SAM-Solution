#ifndef MAIN_CONTROLLER_HPP_
# define MAIN_CONTROLLER_HPP_

# include <QApplication>

class NetworkClientManager;

class MainController : public QObject
{
    Q_OBJECT

private:
    QApplication _qtCore;
    NetworkClientManager *_network = NULL;

public:
    MainController(int, char **);
    ~MainController();

    int run();

private:
    bool _initNetwork();
};

#endif // !MAIN_CONTROLLER_HPP_

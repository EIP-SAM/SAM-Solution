#ifndef MAINCONTROLLER_HPP_
# define MAINCONTROLLER_HPP_

# include <QApplication>

class NetworkClientManager;
//class GUIController;

class MainController : public QObject
{
    Q_OBJECT

private:
    QApplication _qtCore;
//    GUIController *_gui = NULL;
    NetworkClientManager *_network = NULL;

public:
    MainController(int, char **);
    ~MainController();

    int run();

private:
//    bool _initGUI();
    bool _initNetwork();
};

#endif // !MAINCONTROLLER_HPP_

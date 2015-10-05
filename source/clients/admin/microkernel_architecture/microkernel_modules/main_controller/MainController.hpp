#ifndef     MAINCONTROLLER_HPP
# define    MAINCONTROLLER_HPP

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

#endif      // MAINCONTROLLER_HPP

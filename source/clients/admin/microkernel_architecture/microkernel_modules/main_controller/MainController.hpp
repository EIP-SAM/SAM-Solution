#ifndef     MAINCONTROLLER_HPP
# define    MAINCONTROLLER_HPP

# include <QApplication>

class GUIController;

class MainController : public QObject
{
    Q_OBJECT

private:
    QApplication _qtCore;
    GUIController *_gui = NULL;

public:
    MainController(int, char **);
    ~MainController();

    int run();

private:
    bool _initGUI();
};

#endif      // MAINCONTROLLER_HPP

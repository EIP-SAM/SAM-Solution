#ifndef     MAINCONTROLLER_H
# define    MAINCONTROLLER_H

# include <QCoreApplication>

class MainController
{
private:
    QCoreApplication _qtCore;

public:
    MainController(int, char **);
    ~MainController();

    int run();
};

#endif      // MAINCONTROLLER_H

#ifndef MAIN_CONTROLLER_HPP_
# define MAIN_CONTROLLER_HPP_

# include <QGuiApplication>
# include "FunctionalitiesManager.hpp"

class MainController : QObject
{
    Q_OBJECT

private:
    QGuiApplication _qtCore;
    FunctionalitiesManager _fctsManager;

public:
    MainController(int &, char **);
    ~MainController();

    int run();
};

#endif // !MAIN_CONTROLLER_HPP_

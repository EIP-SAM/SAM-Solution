#ifndef MAIN_CONTROLLER_HPP_
# define MAIN_CONTROLLER_HPP_

# include <QGuiApplication>
# include "FunctionalitiesManager.hpp"
# include "InstructionBus.hpp"

class MainController : QObject
{
    Q_OBJECT

private:
    QGuiApplication _qtCore;
    FunctionalitiesManager _fctsManager;
    InstructionBus _instructionBus;

public:
    MainController(int &, char **);
    ~MainController();

    int run();
};

#endif // !MAIN_CONTROLLER_HPP_

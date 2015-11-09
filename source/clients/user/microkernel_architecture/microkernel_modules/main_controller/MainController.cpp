#define __MAIN_CONTROLLER_NO_GLOBAL_DECL
#include "MainController.hpp"

MainController *mainController = NULL;

MainController::MainController(int &ac, char **av)
    : _qtCore(ac, av), _fctsManager(this)
{
    mainController = this;
}

MainController::~MainController()
{
}

int MainController::run()
{
    if (!_instructionBus.init() || !_fctsManager.init())
        return (-1);
    return (_qtCore.exec());
}

InstructionBus &MainController::getInstructionBus()
{
    return _instructionBus;
}

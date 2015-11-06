#include "MainController.hpp"

MainController::MainController(int &ac, char **av)
    : _qtCore(ac, av), _fctsManager(this)
{
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

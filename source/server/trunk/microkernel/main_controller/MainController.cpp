#include "MainController.hpp"

MainController::MainController(int ac, char **av)
    : _qtCore(ac, av)
{
}

MainController::~MainController()
{
}

int MainController::run()
{
    return (_qtCore.exec());
}

#define __MAIN_CONTROLLER_PRIVATE_DECL
#include "MainController.hpp"

MainController::MainController(int &ac, char **av)
    : AMainController(SAM_ADMIN_CLIENT), _qtCore(ac, av)
{
    mainController = !mainController ? this : mainController;
}

MainController::~MainController()
{
}

int MainController::run()
{
    return !_init() ? -1 : _qtCore.exec();
}

#define __MAIN_CONTROLLER_PRIVATE_DECL
#include "MainController.hpp"

//
// Constructor
//
MainController::MainController(int &ac, char **av)
    : AMainController(SAM_USER_CLIENT), _qtCore(ac, av)
{
    mainController = !mainController ? this : mainController;
}

//
// Destructor
//
MainController::~MainController()
{
}

//
// Entry point of the main controller
//
int MainController::run()
{
    return !_init() ? -1 : _qtCore.exec();
}

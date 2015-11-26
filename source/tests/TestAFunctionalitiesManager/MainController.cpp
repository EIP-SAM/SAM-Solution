#define __MAIN_CONTROLLER_PRIVATE_DECL
#include <QTimer>
#include "MainController.hpp"

//
// Constructor
//
MainController::MainController(int &ac, char **av)
    : AMainController(SAM_SERVER), _qtCore(ac, av)
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

//
// Get functionalities manager
//
BasicFunctionalitiesManager &MainController::getFctsManager()
{
    return _fctsManager;
}

//
// Get instruction bus
//
InstructionBus &MainController::getInstructionBus()
{
    return _instructionBus;
}

//
// Get QtCore
//
QCoreApplication &MainController::getQtCore()
{
    return _qtCore;
}

//
// Quit qtCore
//
void MainController::quitQtCore()
{
    QTimer::singleShot(10000, &_qtCore, SLOT(quit()));
}
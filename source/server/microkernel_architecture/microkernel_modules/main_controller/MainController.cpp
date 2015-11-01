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
    if (!_initFctsManager())
        return (-1);
    return (_qtCore.exec());
}

bool MainController::_initFctsManager()
{
    if (!(_fctsManager = new (std::nothrow) FunctionalitiesManager()))
	return false;
    if (!_fctsManager->init())
	return false;
    if (!connect(_fctsManager, SIGNAL(readyToDelete),
		 this, SLOT(_deleteFctsManager)))
	return false;
}

void MainController::_deleteFctsManager()
{
    if (_fctsManager)
	delete _fctsManager;
}

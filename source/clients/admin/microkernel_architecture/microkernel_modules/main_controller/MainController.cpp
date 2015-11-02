#include "MainController.hpp"
#include <QDebug>

MainController::MainController(int ac, char **av)
    : _qtCore(ac, av), _fctsManager(NULL)
{
}

MainController::~MainController()
{
    if (_fctsManager)
	delete _fctsManager;
}

int MainController::run()
{
    qDebug() << Q_FUNC_INFO;

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
    _fctsManager = NULL;
}

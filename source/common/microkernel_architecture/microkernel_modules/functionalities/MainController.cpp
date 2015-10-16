#include "MainController.hpp"

MainController::MainController(int ac, char **av)
    : _qtCore(ac, av)
{
}

MainController::~MainController()
{
    delete _fctsManager;
}

int MainController::run()
{
    if (!_initFctsManager())
        return (-1);

    return (_qtCore.exec());
}

bool MainController::_initFctsManager()
{
    if (!(_fctsManager = new FunctionalitiesManager()))
        return (false);

    connect(_fctsManager, SIGNAL(quit()), this, SLOT(quit()));
    connect(_fctsManager, SIGNAL(readyToDelete()), &_qtCore, SLOT(quit())); 
    _fctsManager->init();
    
    return (true);
}

void MainController::quit()
{
  _fctsManager->shutdown();
}

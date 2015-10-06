#include "MainController.hpp"
#include "GUIController.hpp"
#include "NetworkClientManager.hpp"

#include <QDebug>

MainController::MainController(int ac, char **av)
    : _qtCore(ac, av)
{
}

MainController::~MainController()
{
    delete _network;
}

int MainController::run()
{
    qDebug() << Q_FUNC_INFO;

    if (!_initNetwork())
    {
        return (-1);
    }
    return (_qtCore.exec());
}

bool MainController::_initNetwork()
{
    qDebug() << Q_FUNC_INFO;

    if (!(_network = new NetworkClientManager(this)))
    {
        return (false);
    }
    _network->startConnection("localhost", 42042);
    return (true);
}

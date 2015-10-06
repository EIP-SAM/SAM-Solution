#include "MainController.hpp"
#include "NetworkServer.hpp"

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
    if (!_initNetwork())
        return (-1);

    return (_qtCore.exec());
}

bool MainController::_initNetwork()
{
    if (!(_network = new NetworkServer(this)))
        return (false);

    _network->start(42042);

    return (true);
}

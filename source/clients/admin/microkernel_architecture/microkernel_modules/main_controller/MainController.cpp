#include "MainController.hpp"
#include "GUIController.hpp"

#include <QDebug>

MainController::MainController(int ac, char **av)
    : _qtCore(ac, av)
{
}

MainController::~MainController()
{
    delete _gui;
}

int MainController::run()
{
    qDebug() << Q_FUNC_INFO;

    if (!_initGUI())
    {
        return (-1);
    }
    return (_qtCore.exec());
}

bool MainController::_initGUI()
{
    qDebug() << Q_FUNC_INFO;

    if (!(_gui = new GUIController(this)))
    {
        return (false);
    }
    _gui->init();
    return (true);
}

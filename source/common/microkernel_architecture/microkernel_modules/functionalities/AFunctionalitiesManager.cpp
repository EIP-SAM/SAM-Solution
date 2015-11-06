#include "AFunctionalitiesManager.hpp"

//
// Constructor and Destructor
//
AFunctionalitiesManager::AFunctionalitiesManager(QObject *parent) : QObject(parent),
                                    _shuttingDown(false)
{
}

AFunctionalitiesManager::~AFunctionalitiesManager()
{
    shutdown();
    qDeleteAll(_externalFcts);
    _externalFcts.clear();
    qDeleteAll(_internalFcts);
    _internalFcts.clear();
    qDeleteAll(_microkernelFcts);
    _microkernelFcts.clear();
//    qDeleteAll(_runningFcts);
//    _runningFcts.clear();
}

//
// Initialize microkernel functionalities in a Qlist
//
bool AFunctionalitiesManager::_initMicrokernelFcts()
{
    foreach(AFunctionality *fct, _microkernelFcts)
	{
        if (!connect(fct, SIGNAL(started()), this, SLOT(_functionalityStarted())) ||
            !connect(fct, SIGNAL(stopped()), this, SLOT(_functionalityStopped())) ||
            !fct->start())
		return false;
	}
    return true;
}


//
// Initialize internal functionalities in a Qlist
//
bool AFunctionalitiesManager::_initInternalFcts()
{
    foreach(AFunctionality *fct, _internalFcts)
	{
        if (!connect(fct, SIGNAL(started()), this, SLOT(_functionalityStarted())) ||
            !connect(fct, SIGNAL(stopped()), this, SLOT(_functionalityStopped())) ||
            !fct->start())
            return false;
	}
    return true;
}

//
// Initialize external functionalities in a Qlist
//
bool AFunctionalitiesManager::_initExternalFcts()
{
    foreach(AFunctionality *fct, _externalFcts)
	{
        if (!connect(fct, SIGNAL(started()), this, SLOT(_functionalityStarted())) ||
            !connect(fct, SIGNAL(stopped()), this, SLOT(_functionalityStopped())) ||
            !fct->start())
            return false;
	}
    return true;
}

//
// Initialize all client's functionalities
//
bool AFunctionalitiesManager::init()
{
    _setFcts();
    if (!_initMicrokernelFcts() ||
        !_initInternalFcts() ||
        !_initExternalFcts())
        return false;
    return true;
}

//
// Stop all running functionalities
//
void AFunctionalitiesManager::shutdown()
{
    _shuttingDown = true;
    if (_runningFcts.count() == 0)
        emit readyToDelete();
    else
        foreach(AFunctionality *fct, _runningFcts)
            fct->stop();
}

//
// Load library with the name given in parameter
// Does nothing for now
//
AFunctionality *AFunctionalitiesManager::loadLibrary(const QString &name)
{
    (void)name;
    return (AFunctionality *)NULL;
}

//
// Slot : Activated when a functionality started
// Store a pointer ont this functionality in a list
//
void AFunctionalitiesManager::_functionalityStarted()
{
    _runningFcts << static_cast<AFunctionality *>(QObject::sender());
}

//
// Slot : Activated when a functionality stops
// Remove the pointer from the running functionalities list
//
void AFunctionalitiesManager::_functionalityStopped()
{
    _runningFcts.removeAll(static_cast<AFunctionality *>(QObject::sender()));
    if (_shuttingDown == true && _runningFcts.count() == 0)
        emit readyToDelete();
}

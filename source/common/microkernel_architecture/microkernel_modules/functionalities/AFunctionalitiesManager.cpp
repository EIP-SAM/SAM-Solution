#include "AFunctionalitiesManager.hpp"
#include "MainController.hpp"

//
// Constructor
//
AFunctionalitiesManager::AFunctionalitiesManager(QObject *parent)
  : QObject(parent), _shuttingDown(false)
{
}

//
// Destructor
//
AFunctionalitiesManager::~AFunctionalitiesManager()
{
    shutdown();
    qDeleteAll(_externalFcts);
    _externalFcts.clear();
    qDeleteAll(_internalFcts);
    _internalFcts.clear();
    qDeleteAll(_microkernelFcts);
    _microkernelFcts.clear();
}

//
// Initialize the functionalities from the given Qlist
//
bool AFunctionalitiesManager::_initFunctionalities(QList<AFunctionality *> &fctList)
{
    for (AFunctionality *fct : fctList)
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
    if (!_initFunctionalities(_microkernelFcts) ||
        !_initFunctionalities(_internalFcts) ||
        !_initFunctionalities(_externalFcts))
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
        for (AFunctionality *fct : _runningFcts)
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
// Getter: Return which system architrecture level has the given functionality
//
AFunctionality::eType AFunctionalitiesManager::getFunctionalityType(AFunctionality::eClientId clientId) const
{
    QList<const QList<AFunctionality *> *> functionalitiesLevels = { &_microkernelFcts, &_internalFcts, &_externalFcts };
    AFunctionality::eType levels[] = { AFunctionality::MICROKERNEL, AFunctionality::INTERNAL, AFunctionality::EXTERNAL };
    int i = 0;

    for (auto functionalities : functionalitiesLevels)
    {
        for (auto functionality : *functionalities)
            if (functionality->getClientId() == clientId && clientId != AFunctionality::eClientId::INVALID)
                return levels[i];
        ++i;
    }
    return AFunctionality::INVALID;
}

//
// Slot : Activated when a functionality started
// Store a pointer ont this functionality in a list
//
void AFunctionalitiesManager::_functionalityStarted()
{
    AFunctionality *fct = NULL;

    fct = static_cast<AFunctionality *>(QObject::sender());
    _runningFcts << fct;
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

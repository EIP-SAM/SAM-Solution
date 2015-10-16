#include <unistd.h>
#include <iostream>
#include "FunctionalitiesManager.hpp"

//
// Constructor and Destructor
//
FunctionalitiesManager::FunctionalitiesManager() : _shuttingDown(false)
{
}

FunctionalitiesManager::~FunctionalitiesManager()
{
  shutdown();
  qDeleteAll(_externalFcts);
  _externalFcts.clear();
  qDeleteAll(_internalFcts);
  _internalFcts.clear();
  qDeleteAll(_microkernelFcts);
  _microkernelFcts.clear();
  qDeleteAll(_runningFcts);
  _runningFcts.clear();
}

//
// Initialize microkernel functionalities in a Qlist
//
bool FunctionalitiesManager::_initMicrokernelFcts()
{
  std::cout << "--MICROKERNEL--" << std::endl;

  _microkernelFcts << new AFunctionality();
  _microkernelFcts << new AFunctionality();

  foreach(AFunctionality *fct, _microkernelFcts)
    {
      if (!connect(fct, SIGNAL(started()),
		   this, SLOT(_functionalityStarted())) ||
	  !connect(fct, SIGNAL(stopped()),
		   this, SLOT(_functionalityStopped())))
	return false;
      if (!fct->start())
	return false;
    }
  return true;
}


//
// Initialize internal functionalities in a Qlist
//
bool FunctionalitiesManager::_initInternalFcts()
{
  std::cout << "--INTERNAL--" << std::endl;

  _internalFcts << new AFunctionality();
  _internalFcts << new AFunctionality();

  foreach(AFunctionality *fct, _internalFcts)
    {
      if (!connect(fct, SIGNAL(started()),
		   this, SLOT(_functionalityStarted())) ||
	  !connect(fct, SIGNAL(stopped()),
		   this, SLOT(_functionalityStopped())))
	return false;
      if (!fct->start())
	return false;
    }
  return true;
}

//
// Initialize external functionalities in a Qlist
//
bool FunctionalitiesManager::_initExternalFcts()
{
  std::cout << "--EXTERNAL--" << std::endl;

  _externalFcts << new AFunctionality();
  _externalFcts << new AFunctionality();

  foreach(AFunctionality *fct, _externalFcts)
    {
      if (!connect(fct, SIGNAL(started()),
		   this, SLOT(_functionalityStarted())) ||
	  !connect(fct, SIGNAL(stopped()),
		   this, SLOT(_functionalityStopped())))
	return false;
      if (!fct->start())
	return false;
    }
  return false;
}

//
// Initialize all client's functionalities 
//
bool FunctionalitiesManager::init()
{
  if (!_initMicrokernelFcts() ||
      !_initInternalFcts() ||
      !_initExternalFcts())
    return false;
  return true;
}

//
// Stop all running functionalities
//
void FunctionalitiesManager::shutdown()
{
  _shuttingDown = true;
  foreach(AFunctionality *fct, _runningFcts)
    fct->stop();
}

//
// Load library with the name given in parameter
//
AFunctionality *FunctionalitiesManager::loadLibrary(const QString &name)
{
  (void)name;
  return new AFunctionality();
}

//
// Slot : Activated when a functionality started
// Store a pointer ont this functionality in a list
//
void FunctionalitiesManager::_functionalityStarted()
{
  _runningFcts << static_cast<AFunctionality *>(QObject::sender());
  std::cout << "Manager : " << QObject::sender() << " started" << std::endl;
  std::cout << "Manager : " << _runningFcts.count() << " currently running" << std::endl;
  if (_runningFcts.count() == 6)
    emit quit();
}

//
// Slot : Activated when a functionality stops
// Remove the pointer from the running functionalities list
//
void FunctionalitiesManager::_functionalityStopped()
{
  _runningFcts.removeAll(static_cast<AFunctionality *>(QObject::sender()));
  if (_shuttingDown == true && _runningFcts.count() == 0)
    emit(readyToDelete());
  std::cout << "Manager : " << QObject::sender() << " stopped" << std::endl;
}

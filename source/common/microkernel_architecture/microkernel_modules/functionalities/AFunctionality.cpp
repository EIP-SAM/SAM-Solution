#include <unistd.h>
#include <iostream>
#include "AFunctionality.hpp"

//
// Constructor and Destructor
//
AFunctionality::AFunctionality() : _thread(NULL), _running(false)
{  
}

AFunctionality::~AFunctionality()
{
  stop();
}

//
// Start the functionnality, threaded by default
// and send a signal to FunctionalitiesManager class
// to keep a trace of what functionalities are running right now
//
bool AFunctionality::start(bool threaded)
{
  if (_running)
    return false;
  if (threaded)
    {
      _thread = new QThread();
      this->moveToThread(_thread);
      if (!connect(_thread, SIGNAL(started()), this, SLOT(_fctStarted())) ||
	  !connect(_thread, SIGNAL(finished()), this, SLOT(_fctFinished())))
	return false;
      _thread->start();
    }
  else
    _fctStarted();
  return true;
}

//
// Stop the functionality and stop the thread if needed
//
void AFunctionality::stop()
{
  if (!_running)
    return ;
  if (_thread)
    {
      _thread->quit();
      _thread->wait();
      delete _thread;
      _thread = NULL;
    }
  else
    emit stopped();
}

//
// Getter on running to attribute
//
bool AFunctionality::isRunning() const
{
  return _running;
}

//
// Slot : tells FunctionalitiesManager that the functionality just started
// called either manually or by the thread
//
void AFunctionality::_fctStarted()
{
  _running = true;
  emit started();
}

//
// Slot : tells FunctionalitiesManager that the functionality just stopped
// called either manually or by the thread
//
void AFunctionality::_fctFinished()
{
  _running = false;
  emit stopped();
}

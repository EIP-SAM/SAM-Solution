#include <unistd.h>
#include <iostream>
#include "AFunctionality.hpp"

//
// Constructor and Destructor
//
AFunctionality::AFunctionality() : _thread(NULL), _running(false)
{  
  std::cout << this << " instanciated" << std::endl;
}

AFunctionality::~AFunctionality()
{
  stop();
  std::cout << this << " destructed" << std::endl;
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
      std::cout << this << " starting its thread" << std::endl;
      _thread = new QThread();
      this->moveToThread(_thread);
      if (!connect(_thread, SIGNAL(started()), this, SLOT(_fctStarted())) ||
	  !connect(_thread, SIGNAL(finished()), this, SLOT(_fctFinished())))
	return false;
      _thread->start();
    }
  else
    {
      std::cout << this << " starting not threaded" << std::endl;
      _fctStarted();
    }
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
  std::cout << this << " emiting starting signal" << std::endl;
  _running = true;
  emit started();
}

//
// Slot : tells FunctionalitiesManager that the functionality just stopped
// called either manually or by the thread
//
void AFunctionality::_fctFinished()
{
  std::cout << this << " emiting ending signal" << std::endl;
  _running = false;
  emit stopped();
}

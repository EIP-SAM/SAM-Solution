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
void AFunctionality::start(bool threaded)
{
  if (_running)
    return ;
  if (threaded)
    {
      std::cout << this << " starting its thread" << std::endl;
      _thread = new QThread();
      this->moveToThread(_thread);
      connect(_thread, SIGNAL(started()), this, SLOT(_fctStarted()));
      connect(_thread, SIGNAL(finished()), this, SLOT(_fctFinished()));
      _thread->start();
      std::cout << this << " is now in a thread" << std::endl;
    }
  else
    {
      std::cout << this << " starting not threaded" << std::endl;
      _fctStarted();
    }
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
// Slot : tells FunctionalitiesManager that the functionality just started
// called either manually or by the thread
//
void AFunctionality::_fctStarted()
{
  std::cout << this << " emiting starting signal" << std::endl;
  _running = true;
  emit started();

  for(int i = 0; i < 5; ++i)
    {
      std::cout << "---------- " << this << " [" << i << "]" << std::endl;
      _thread->sleep(5);
    }
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

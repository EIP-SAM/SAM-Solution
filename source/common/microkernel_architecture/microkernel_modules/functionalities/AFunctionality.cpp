#include "AFunctionality.hpp"

//
// Constructor and Destructor
//
AFunctionality::AFunctionality()
{
  _thread = new QThread();
}

AFunctionality::~AFunctionality()
{
  stop();
  _thread->quit();
  _thread->wait();
}

//
// Start a new thread and send a signal to FunctionalitiesManager
// class with this AFunctionality object to keep a trace of what
// functionalities are running right now
//
void AFunctionality::start(bool threaded)
{
  if (threaded && _thread != null) {
    connect(this);
    _thread.start();
  }
}

//
// Stop thread
//
void AFunctionality::stop()
{
  _thread.exit();
}

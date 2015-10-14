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
// Start a new thread
//
void AFunctionality::start(bool threaded)
{
  if (threaded && _thread != null) {
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

//
// Connect to another class SLOT
//
void AFunctionality::signal_starded()
{
  
}

#include "AFunctionality.hpp"
#include "FunctionalitiesManager.hpp"

//
// Constructor and Destructor
//
AFunctionality::AFunctionality()
{

}

AFunctionality::~AFunctionality()
{
  stop();
  quit();
  wait();
}

//
// Start a new thread and send a signal to FunctionalitiesManager
// class with this AFunctionality object to keep a trace of what
// functionalities are running right now
//
void AFunctionality::start(bool threaded, FunctionalitiesManager &manager)
{
  if (threaded != null) {
    connect(this, SIGNAL(started(this)), manager, SLOT());
    start();
  }
}

//
// Stop thread
//
void AFunctionality::stop()
{
  quit();
}

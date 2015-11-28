#include "AFunctionality.hpp"
#include "MainController.hpp"

//
// Constructor
//
AFunctionality::AFunctionality(eClientId clientId, bool threaded)
    : AInstructionBusClient(clientId),
      _thread(NULL), _running(false), _threaded(threaded)
{
    if (!_threaded)
        connect(this, SIGNAL(instructionPushed()), this, SLOT(onInstructionPushed()));
    mainController->registerClient(_clientId, this);
}

//
// Destructor
//
AFunctionality::~AFunctionality()
{
    stop();
}

//
// Start the functionnality, threaded by default
// and send a signal to FunctionalitiesManager class
// to keep a trace of what functionalities are running right now
//
bool AFunctionality::start()
{
    if (_running)
        return false;
    if (_threaded)
	{
        _thread = new QThread();
        this->moveToThread(_thread);
        if (!connect(_thread, SIGNAL(started()), this, SLOT(_fctStarted())) ||
            !connect(_thread, SIGNAL(started()), this, SLOT(_run())) ||
            !connect(_thread, SIGNAL(finished()), this, SLOT(_fctFinished())))
            return false;
	    _thread->start();
	}
    else
    {
        _fctStarted();
        _run();
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

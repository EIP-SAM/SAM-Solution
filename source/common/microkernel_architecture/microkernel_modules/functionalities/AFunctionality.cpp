#include "AFunctionality.hpp"
#include "MainController.hpp"

//
// Constructor and Destructor
//
AFunctionality::AFunctionality(eClientId clientId)
    : AInstructionBusClient(clientId),
      _thread(NULL), _running(false), _threaded(true)
{
    mainController->getInstructionBus().registerClient(_clientId, this);
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
bool AFunctionality::start()
{
    if (_running)
        return false;
    if (_threaded)
	{
        _thread = new QThread();
        this->moveToThread(_thread);
        if (!connect(_thread, SIGNAL(started()), this, SLOT(_fctStarted())) ||
            !connect(_thread, SIGNAL(started()), this, SLOT(run())) ||
            !connect(_thread, SIGNAL(finished()), this, SLOT(_fctFinished())))
            return false;
	    _thread->start();
	}
    else
    {
        _fctStarted();
        run();
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
// `_threaded` attribute setter
// Plus repercussion on the parent class when using a
// non-threaded functionality
//
void AFunctionality::setThreaded(bool threaded)
{
    _threaded = threaded;
    if (!_threaded)
        connect(this, SIGNAL(instructionPushed()), this, SLOT(onInstructionPushed()));
}

//
// `_threaded` attribute getter
//
bool AFunctionality::isThreaded() const
{
    return _threaded;
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

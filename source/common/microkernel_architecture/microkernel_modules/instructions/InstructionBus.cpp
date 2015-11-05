#include "InstructionBus.hpp"
#include "AInstruction.hpp"
#include <QMutexLocker>

#include <QDebug>

InstructionBus::InstructionBus()
    : _thread(NULL), _mutex(NULL)
{
}

InstructionBus::~InstructionBus()
{
    //
    // Do it properly !
    // And do not forget to free the QQueue* in _transmitterClientsInstructions
    //
    if (_thread)
    {
        _thread->quit();
        delete _thread;
    }
    delete _mutex;
}

//
// Initialize the instruction bus
// Start its working thread
//
bool InstructionBus::init()
{
    if (_thread)
    {
        qDebug() << "Warning: Instruction bus already initialized, does nothing";
        return true;
    }
    if (!(_thread = new (std::nothrow) QThread) ||
        !(_mutex = new (std::nothrow) QMutex))
    {
        qDebug() << "Error:" << Q_FUNC_INFO << ": Memory allocation failure";
        delete _thread;
        _thread = NULL;
        return false;
    }
    if (!connect(_thread, SIGNAL(started()), this, SLOT(_run())))
    {
        qDebug() << "Error: Fatal error in" << Q_FUNC_INFO;
        delete _thread;
        delete _mutex;
        _thread = NULL;
        _mutex = NULL;
        return false;
    }
    _thread->start();
    return true;
}

//
// Register an instruction bus client in the _clientsRegister map
// Does nothing if any parameter is invalid
//
bool InstructionBus::registerClient(AInstructionBusClient::eClientId clientId, AInstructionBusClient *client)
{
    if (!_thread || !_mutex)
    {
        qDebug() << "Error: Instruction bus not yet initialized";
        return false;
    }

    QMutexLocker _locker(_mutex);

    if (clientId == AInstructionBusClient::INVALID || !client)
    {
        qDebug() << "Error: Invalid client or client id";
        return false;
    }
    if (!_clientsRegister.contains(clientId))
    {
        QQueue<AInstruction *> *instructionsQueue = NULL;

        if (!(instructionsQueue = new (std::nothrow) QQueue<AInstruction *>))
        {
            qDebug() << "Error:" << Q_FUNC_INFO << ": Memory allocation failure";
            return false;
        }
        _clientsRegister.insert(clientId, client);
        _transmitterClientsInstructions.insert(client, instructionsQueue);
        return true;
    }
    qDebug() << "Error: A client is already registered with this client id";
    return false;
}

//
// Theoreticaly called from an `AInstructionBusClient` subclass
// Pushes an instruction in the transmitter queue that will be
// proccessed later in the working thread `_thread`
//
bool InstructionBus::pushInstruction(AInstruction *instruction)
{
    QQueue<AInstruction *> *transmitterClientInstructions = NULL;
    AInstructionBusClient *transmiterClient = NULL;
    QMutexLocker locker(_mutex);

    if (!_thread || !_mutex)
    {
        qDebug() << "Error: Instruction bus not yet initialized";
        return false;
    }
    if (!instruction)
    {
        qDebug() << "Error: Invalid instruction";
        return false;
    }
    transmiterClient = instruction->getTransmitter();
    if (!transmiterClient || !(_transmitterClientsInstructions.contains(transmiterClient)))
    {
        qDebug() << "Error: Unknown transmitter client";
        return false;
    }
    if (!(transmitterClientInstructions = _transmitterClientsInstructions[transmiterClient]))
    {
        qDebug() << "Error:" << Q_FUNC_INFO << "internal error";
        return false;
    }
    transmitterClientInstructions->enqueue(instruction);
    return true;
}

//
// Instruction bus entry point for the working thread `_thread`
// Infinite loop where the instructions pushed via `pushInstruction()`
// are proccessed
// The proccess consists of the checking of the instruction validity
// plus the dispataching of this instruction to the `AInstructionBusClient`
// supposed to receive it
//
void InstructionBus::_run()
{
    QQueue<AInstruction *> *instructionsQueue = NULL;

    qDebug() << Q_FUNC_INFO;
    while (42)
    {
        _mutex->lock();

        auto it = _transmitterClientsInstructions.begin();

        while (it != _transmitterClientsInstructions.end())
        {
            instructionsQueue = *it;
            while (!instructionsQueue->empty())
                _dispatchInstruction(instructionsQueue->dequeue());
        }

        _mutex->unlock();
    }
}

//
// Check the validity of the AInstruction and dispatch it to
// the given `AInstructionBusClient` receiver
//
inline void InstructionBus::_dispatchInstruction(AInstruction *instruction)
{
    AInstructionBusClient *receiverClient = NULL;

    if (!instruction)
        return ;
    if (!_clientsRegister.contains(instruction->getReceiver()))
        return ;
    receiverClient = _clientsRegister[instruction->getReceiver()];
    receiverClient->pushInstruction(instruction);
}

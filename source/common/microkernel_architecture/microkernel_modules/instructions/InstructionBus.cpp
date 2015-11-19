#include "InstructionBus.hpp"
#include "AInstruction.hpp"
#include <QMutexLocker>
#include <QDebug>

//
// Constructor
//
InstructionBus::InstructionBus(QObject *parent)
    : QObject(parent), _thread(NULL), _mutex(NULL)
{
}

//
// Destructor
// Note: Exit is quick and dirty for now, need to do it
// Note2: And do not forget to free the QQueue* in _transmitterClientsInstructions
//
InstructionBus::~InstructionBus()
{
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
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
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
    this->moveToThread(_thread);
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
// Register an instruction bus client in the _localClientsRegister map
// Does nothing if any parameter is invalid
//
bool InstructionBus::registerClient(AInstructionBusClient::eClientId clientId, AInstructionBusClient *client)
{
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

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
    if (!_localClientsRegister.contains(clientId))
    {
        QQueue<AInstruction *> *instructionsQueue = NULL;

        if (!(instructionsQueue = new (std::nothrow) QQueue<AInstruction *>))
        {
            qDebug() << "Error:" << Q_FUNC_INFO << ": Memory allocation failure";
            return false;
        }
        _localClientsRegister.insert(clientId, client);
        _transmitterClientsInstructions.insert(client, instructionsQueue);
        qDebug() << "Success: Client" << client << "with id" << clientId
                 << "successfuly registered";
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

    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
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
    transmiterClient = (AInstructionBusClient *)instruction->getLocalTransmitter();
    if (!transmiterClient || !_transmitterClientsInstructions.contains(transmiterClient))
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
    QMap<AInstructionBusClient*, QQueue<AInstruction*>*>::iterator it;
    QQueue<AInstruction *> *instructionsQueue = NULL;

    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    while (42)
    {
        _mutex->lock();
        it = _transmitterClientsInstructions.begin();
        while (it != _transmitterClientsInstructions.end())
        {
            instructionsQueue = *it;
            while (!instructionsQueue->empty())
            {
                _dispatchInstruction(instructionsQueue->dequeue());
            }
            ++it;
        }
        _mutex->unlock();
        QThread::msleep(30);
    }
}

//
// Check the validity of the AInstruction and dispatch it to
// the given `AInstructionBusClient` receiver
//
inline void InstructionBus::_dispatchInstruction(AInstruction *instruction)
{
    AInstructionBusClient *receiverClient = NULL;

    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    if (!instruction)
        return ;
    if (!_localClientsRegister.contains(instruction->getFinalReceiver()))
    {
        if (!_remoteClientsRegister.contains(instruction->getFinalReceiver()) ||
            !_localClientsRegister.contains(AInstructionBusClient::eClientId::NETWORK_MANAGER))
        {
            qDebug() << "Error:" << Q_FUNC_INFO << ": Unknown receiver, instruction deleted";
            delete instruction;
            return ;
        }
        receiverClient = _localClientsRegister[AInstructionBusClient::eClientId::NETWORK_MANAGER];
    }
    else
        receiverClient = _localClientsRegister[instruction->getFinalReceiver()];
    receiverClient->pushInstruction(instruction);
    qDebug() << "Instruction pushed to client id" << receiverClient->getClientId();
    emit receiverClient->instructionPushed();
}

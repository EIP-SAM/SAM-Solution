#include "AInstructionBusClient.hpp"
#include "AInstruction.hpp"

#include <QDebug>
#include <QThread>

AInstructionBusClient::AInstructionBusClient(eClientId clientId)
    : QObject(), _clientId(clientId)
{
}

AInstructionBusClient::~AInstructionBusClient()
{
    AInstruction *instruction = NULL;
    QMutexLocker locker(&_mutex);

    while (!_instructions.empty())
    {
        instruction = _instructions.dequeue();
        delete instruction;
    }
}

//
// Theoreticaly called from the `InstructionBus`
// Push an instruction in the client queue `_instructions`
//
void AInstructionBusClient::pushInstruction(AInstruction *instruction)
{
    QMutexLocker locker(&_mutex);

    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    _instructions.enqueue(instruction);
}

//
// Enable `onInstructionPushed()` slot
// This method needs to be called before
// `InstructionBus::registerClient()` to work
//
void AInstructionBusClient::enableInstructionPushedSlot()
{
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    _slotEnabled = true;
}

//
// Getter: Return the client id
//
AInstructionBusClient::eClientId AInstructionBusClient::getClientId() const
{
    return _clientId;
}

//
// Getter: Return true is `onInstructionPushed()` is supposed
// to be enabled
//
bool AInstructionBusClient::instructionPushedSlotEnabled() const
{
    return _slotEnabled;
}

//
// Pop and return the next instruction in the queue `_instructions`
// Return NULL if there is no instruction
//
AInstruction *AInstructionBusClient::_popInstruction()
{
    AInstruction *instruction = NULL;

    _mutex.lock();
    if (!_instructions.empty())
        instruction = _instructions.dequeue();
    _mutex.unlock();
    return instruction;
}

//
// Signal to the `AInstructionBusClient` that a new
// `AInstruction` has been pushed in the queue `_instructions`
// Note: This method needs to be overrided to work properly
// Note2: See the note at the top of AInstructionBusClient.hpp
//
void AInstructionBusClient::onInstructionPushed()
{
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId() << ": Needs to be overrided";
}

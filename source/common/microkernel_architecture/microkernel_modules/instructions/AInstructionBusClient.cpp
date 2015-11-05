#include "AInstructionBusClient.hpp"
#include "AInstruction.hpp"

AInstructionBusClient::AInstructionBusClient()
    : _clientId(INVALID)
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

    _instructions.enqueue(instruction);
}

//
// Getter: Return the client id
//
AInstructionBusClient::eClientId AInstructionBusClient::getClientId() const
{
    return _clientId;
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

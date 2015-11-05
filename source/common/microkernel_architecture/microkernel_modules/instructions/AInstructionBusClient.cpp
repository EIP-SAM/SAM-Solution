#include "AInstructionBusClient.hpp"

AInstructionBusClient::AInstructionBusClient(AInstructionBusClient::eClientId clientId, QQueue<AInstruction *> instructions)
    : _clientId(clientId), _instructions(instructions)
{
}

AInstructionBusClient::~AInstructionBusClient()
{
}

void AInstructionBusClient::setClientId(AInstructionBusClient::eClientId clientId)
{
    _clientId = clientId;
}

void AInstructionBusClient::setInstructions(QQueue<AInstruction *> instructions)
{
    _instructions = instructions;
}

//
// (appel execute depuis un autre thread -> protection via QMutex) push une AInstruction dans la queue
//
void AInstructionBusClient::pushInstruction(AInstruction *instruction)
{
    _instructions.enqueue(instruction);
}

//
// pop et retourne un AInstruction
//
AInstruction *AInstructionBusClient::_popInstruction()
{
    return _instructions.dequeue();
}

AInstructionBusClient::eClientId AInstructionBusClient::getClientId() const
{
    return _clientId;
}

QQueue<AInstruction *> AInstructionBusClient::getInstructions() const
{
    return _instructions;
}

//
// true si il y a au moins une AInstruction dans la queue
//
bool AInstructionBusClient::_hasInstructions()
{
    return !_instructions.isEmpty();
}

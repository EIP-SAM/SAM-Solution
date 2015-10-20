#include "AInstructionBusClient.hpp"

AInstructionBusClient::AInstructionBusClient(AInstructionBusClient::eClientId clientId, QQueue<AInstruction *> instructions)
{
    //ctor
    this->_clientId = clientId;
    this->_instructions = instructions;
}

AInstructionBusClient::~AInstructionBusClient()
{
    //dtor
}

AInstructionBusClient::eClientId AInstructionBusClient::getClientId() const
{
    return this->_clientId;
}

void AInstructionBusClient::setClientId(AInstructionBusClient::eClientId clientId)
{
    this->_clientId = clientId;
}

QQueue<AInstruction *> AInstructionBusClient::getInstructions() const
{
    return this->_instructions;
}

void AInstructionBusClient::setInstructions(QQueue<AInstruction *> instructions)
{
    this->_instructions = instructions;
}

void AInstructionBusClient::pushInstruction(AInstruction *instruction)
{
    // (appel executé depuis un autre thread -> protection via QMutex) push une AInstruction dans la queue
    this->_instructions.enqueue(instruction);
}

bool AInstructionBusClient::_hasInstructions()
{
    // true si il y a au moins une AInstruction dans la queue
    return !this->_instructions.isEmpty();
}

AInstruction *AInstructionBusClient::_popInstruction()
{
    // pop et retourne un AInstruction
    return this->_instructions.dequeue();
}



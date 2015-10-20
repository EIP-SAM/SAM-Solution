#include "AInstruction.hpp"

AInstruction::AInstruction(AInstructionBusClient *transmitter,
			   AInstructionBusClient::eClientId receiver, int instructionId)
{
    // ctor
    this->_transmitter = transmitter;
    this->_receiver = receiver;
    this->_instructionId = instructionId;
}

AInstruction::~AInstruction()
{
    // dtor
}

AInstructionBusClient *AInstruction::getTransmitter() const
{
    return this->_transmitter;
}

void AInstruction::setTransmitter(AInstructionBusClient *transmitter)
{
    this->_transmitter = transmitter;
}

AInstructionBusClient::eClientId AInstruction::getReceiver() const
{
    return this->_receiver;
}

void AInstruction::setReceiver(AInstructionBusClient::eClientId receiver)
{
    this->_receiver = receiver;
}

int AInstruction::getInstructionId() const
{
    return this->_instructionId;
}

void AInstruction::setInstructionId(int instructionId)
{
    this->_instructionId = instructionId;
}


#include "AInstruction.hpp"

AInstruction::AInstruction(AInstructionBusClient *transmitter,
                           AInstructionBusClient::eClientId receiver, int instructionId)
    : _transmitter(transmitter), _receiver(receiver), _instructionId(instructionId)
{
}

AInstruction::~AInstruction()
{
}

void AInstruction::setTransmitter(AInstructionBusClient *transmitter)
{
    _transmitter = transmitter;
}

void AInstruction::setReceiver(AInstructionBusClient::eClientId receiver)
{
    _receiver = receiver;
}

void AInstruction::setInstructionId(int instructionId)
{
    _instructionId = instructionId;
}

AInstructionBusClient *AInstruction::getTransmitter() const
{
    return _transmitter;
}

AInstructionBusClient::eClientId AInstruction::getReceiver() const
{
    return _receiver;
}

int AInstruction::getInstructionId() const
{
    return _instructionId;
}

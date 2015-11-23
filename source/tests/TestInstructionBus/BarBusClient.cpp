#include "BarBusClient.hpp"

BarBusClient::BarBusClient()
{
}

BarBusClient::BarBusClient(eClientId clientId)
    : AInstructionBusClient(clientId)
{
}

AInstruction *BarBusClient::getInstruction()
{
    return _popInstruction();
}

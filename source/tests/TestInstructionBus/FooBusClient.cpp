#include "FooBusClient.hpp"

FooBusClient::FooBusClient()
{
}

FooBusClient::FooBusClient(eClientId clientId)
    : AInstructionBusClient(clientId)
{
}

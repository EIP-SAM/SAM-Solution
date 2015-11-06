#include "ANetworkInstruction.hpp"

ANetworkInstruction::ANetworkInstruction()
    : AInstruction()
{
}

ANetworkInstruction::ANetworkInstruction(const ANetworkInstruction &o)
    : AInstruction(o) //, _foo(o._foo) ...
{
}

ANetworkInstruction::ANetworkInstruction(const QByteArray &data)
    : AInstruction(data)
{
}

ANetworkInstruction::~ANetworkInstruction()
{
}

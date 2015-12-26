#define __DISCONNECT_PRIVATE_DEF
#include "Disconnect.hpp"
#include "ReturnType.hpp"

//
// Constructor
//
Disconnect::Disconnect(eProgId transmitterProgId,
		       AInstructionBusClient::eClientId firstTransmitterId,
		       AInstructionBusClient::eClientId finalReceiverId)
{
    _initInstructionHeader(transmitterProgId, firstTransmitterId, finalReceiverId);
}

//
// Copy Constructor
//
Disconnect::Disconnect(Disconnect *disconnect)
{
    _initInstructionHeader(disconnect->getTransmitterProgId(), disconnect->getFirstTransmitter(),
			   disconnect->getFinalReceiver());
}

//
// Destructor
//
Disconnect::~Disconnect()
{
}

//
// Init all elements of the instruction's header
//
void Disconnect::_initInstructionHeader(eProgId transmitterProgId,
					AInstructionBusClient::eClientId firstTransmitterId,
					AInstructionBusClient::eClientId finalReceiverId)
{
    resetMagicNumber();
    setTransmitterProgId(transmitterProgId);
    setFirstTransmitter(firstTransmitterId);
    setFinalReceiver(finalReceiverId);
    setInstructionCode(_INSTRUCTION_CODE);
    setReturnType(ReturnType::BOOLEAN);
}

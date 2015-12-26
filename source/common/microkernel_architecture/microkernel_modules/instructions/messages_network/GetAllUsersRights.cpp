#define __GET_ALL_USERS_RIGHTS_PRIVATE_DEF
#include "GetAllUsersRights.hpp"
#include "ReturnType.hpp"

//
// Constructor
//
GetAllUsersRights::GetAllUsersRights(eProgId transmitterProgId,
				     AInstructionBusClient::eClientId firstTransmitterId,
				     AInstructionBusClient::eClientId finalReceiverId)
{
    _initInstructionHeader(transmitterProgId, firstTransmitterId, finalReceiverId);
}

//
// Copy constructor
//
GetAllUsersRights::GetAllUsersRights(GetAllUsersRights *getAllUsersRights)
{
    _initInstructionHeader(getAllUsersRights->getTransmitterProgId(), getAllUsersRights->getFirstTransmitter(),
			   getAllUsersRights->getFinalReceiver());
}

//
// Destructor
//
GetAllUsersRights::~GetAllUsersRights()
{
}

//
// Init all elements of the instruction's header
//
void GetAllUsersRights::_initInstructionHeader(eProgId transmitterProgId,
					       AInstructionBusClient::eClientId firstTransmitterId,
					       AInstructionBusClient::eClientId finalReceiverId)
{
    resetMagicNumber();
    setTransmitterProgId(transmitterProgId);
    setFirstTransmitter(firstTransmitterId);
    setFinalReceiver(finalReceiverId);
    setInstructionCode(_INSTRUCTION_CODE);
    setReturnType(ReturnType::QLIST_USERS);
}

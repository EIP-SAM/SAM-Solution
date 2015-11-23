#include "AMainController.hpp"

//
// Constructor
//
AMainController::AMainController(eProgId progId)
    : _fctsManager(this), _progId(progId)
{
}

//
// Destructor
//
AMainController::~AMainController()
{
}

//
// Internal initializer
//
bool AMainController::_init()
{
    return _instructionBus.init() && _fctsManager.init();
}

//
// Wrapper for `InstructionBus::registerClient()`
//
bool AMainController::registerClient(AInstructionBusClient::eClientId clientId, AInstructionBusClient *client)
{
    return _instructionBus.registerClient(clientId, client);
}

//
// Wrapper for `InstructionBus::pushInstruction()`
//
bool AMainController::pushInstruction(AInstruction *instruction)
{
    return _instructionBus.pushInstruction(instruction);
}

//
// Getter: Return program id (server, client user, client admin)
//
eProgId AMainController::getProgId() const
{
    return _progId;
}

//
// Getter: Return type of a functionality (microkernel, internal, external)
//
AFunctionality::eType AMainController::getFunctionalityType(AFunctionality::eClientId clientId) const
{
    return _fctsManager.getFunctionalityType(clientId);
}

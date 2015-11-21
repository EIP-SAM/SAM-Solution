#include "AMainController.hpp"

AMainController::AMainController(eProgId progId)
    : _fctsManager(this), _progId(progId)
{
}

AMainController::~AMainController()
{
}

bool AMainController::_init()
{
    return _instructionBus.init() && _fctsManager.init();
}

bool AMainController::registerClient(AInstructionBusClient::eClientId clientId, AInstructionBusClient *client)
{
    return _instructionBus.registerClient(clientId, client);
}

bool AMainController::pushInstruction(AInstruction *instruction)
{
    return _instructionBus.pushInstruction(instruction);
}

AMainController::eProgId AMainController::getProgId() const
{
    return _progId;
}

AFunctionality::eType AMainController::getFunctionalityType(AFunctionality::eClientId clientId) const
{
    return _fctsManager.getFunctionalityType(clientId);
}

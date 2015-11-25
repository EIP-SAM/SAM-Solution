#include "BasicAMainController.hpp"

//
// Constructor
//
BasicAMainController::BasicAMainController(eProgId progId)
    : _basicFctsManager(this), _progId(progId)
{
}

//
// Destructor
//
BasicAMainController::~BasicAMainController()
{
}

//
// Entry point of the controller
//
int BasicMainController::run()
{
    return !_init() ? -1 : _qtCore.exec();
}

//
// Internal initializer
//
bool BasicAMainController::_init()
{
    return _instructionBus.init() && _basicFctsManager.init();
}

//
// Wrapper for `InstructionBus::registerClient()`
//
bool BasicAMainController::registerClient(AInstructionBusClient::eClientId clientId, AInstructionBusClient *client)
{
    return _instructionBus.registerClient(clientId, client);
}

//
// Wrapper for `InstructionBus::pushInstruction()`
//
bool BasicAMainController::pushInstruction(AInstruction *instruction)
{
    return _instructionBus.pushInstruction(instruction);
}

//
// Getter: Return program id (server, client user, client admin)
//
eProgId BasicAMainController::getProgId() const
{
    return _progId;
}

//
// Getter: Return type of a functionality (microkernel, internal, external)
//
AFunctionality::eType BasicAMainController::getFunctionalityType(AFunctionality::eClientId clientId) const
{
    return _fctsManager.getFunctionalityType(clientId);
}

//
// Getter: Return the basicFunctionalitiesManger
//
BasicFunctionalitiesManager &BasicMainController::getBasicFonctionalitiesManager() const
{
    return _basicFctsManager;
}

//
// Getter: Return the instructionBus
//
InstructionBus &BasicMainController::getInstructionBus() const
{
    return _insctructionBus;
}
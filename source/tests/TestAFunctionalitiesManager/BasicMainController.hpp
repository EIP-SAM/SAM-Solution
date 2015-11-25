#ifndef BASIC_MAIN_CONTROLLER_HPP
# define BASIC_MAIN_CONTROLLER_HPP

# include "AFunctionalitiesManager.hpp"
# include "InstructionBus.hpp"
# include "eProgId.hpp"

class BasicMainController : public QObject
{
    Q_OBJECT
    
private:
    BasicFunctionalitiesManager _basicFctsManager;
    InstructionBus _instructionBus;
    const eProgId _progId;

protected:
    BasicMainController(eProgId);

public:
    ~BasicMainController();

    int run();

protected:
    bool _init();

public:
    bool registerClient(AInstructionBusClient::eClientId, AInstructionBusClient *);
    bool pushInstruction(AInstruction *);

    eProgId getProgId() const;
    AFunctionality::eType getFunctionalityType(AFunctionality::eClientId) const;
}

#endif // !BASIC_MAIN_CONTROLLER_HPP
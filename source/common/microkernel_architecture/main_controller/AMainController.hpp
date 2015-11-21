#ifndef AMAIN_CONTROLLER_HPP_
# define AMAIN_CONTROLLER_HPP_

# include "FunctionalitiesManager.hpp"
# include "InstructionBus.hpp"

class AMainController : public QObject
{
    Q_OBJECT

public:
    enum eProgId
    {
        SAM_SERVER = 1,
        SAM_ADMIN_CLIENT = 2,
        SAM_USER_CLIENT = 3
    };

private:
    FunctionalitiesManager _fctsManager;
    InstructionBus _instructionBus;
    const eProgId _progId;

protected:
    AMainController(eProgId);

public:
    virtual ~AMainController();

    virtual int run() = 0;

protected:
    bool _init();

public:
    bool registerClient(AInstructionBusClient::eClientId, AInstructionBusClient *);
    bool pushInstruction(AInstruction *);

    eProgId getProgId() const;
    AFunctionality::eType getFunctionalityType(AFunctionality::eClientId) const;
};

#endif // !AMAIN_CONTROLLER_HPP_

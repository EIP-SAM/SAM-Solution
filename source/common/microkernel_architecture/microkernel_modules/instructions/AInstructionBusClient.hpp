#ifndef AINSTRUCTION_BUS_CLIENT_HPP_
# define AINSTRUCTION_BUS_CLIENT_HPP_

# include <QQueue>

class AInstruction;

class AInstructionBusClient
{
public:
    enum eClientId
    {
        INVALID = 0
    };

private:
    eClientId _clientId;
    QQueue<AInstruction *> _instructions;

public:
    AInstructionBusClient(eClientId, QQueue<AInstruction *>);
    virtual ~AInstructionBusClient();

    void setClientId(eClientId);
    void setInstructions(QQueue<AInstruction *>);
    void pushInstruction(AInstruction *);
    AInstruction *_popInstruction();

    eClientId getClientId() const;
    QQueue<AInstruction *> getInstructions() const;
    bool _hasInstructions();
};

#endif // !AINSTRUCTION_BUS_CLIENT_HPP_

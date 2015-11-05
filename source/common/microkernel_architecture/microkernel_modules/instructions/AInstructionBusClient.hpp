#ifndef AINSTRUCTION_BUS_CLIENT_HPP_
# define AINSTRUCTION_BUS_CLIENT_HPP_

# include <QMutex>
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
    QMutex _mutex;
    QQueue<AInstruction *> _instructions;

protected:
    eClientId _clientId;

public:
    AInstructionBusClient();
    virtual ~AInstructionBusClient();

    void pushInstruction(AInstruction *);
    eClientId getClientId() const;

protected:
    AInstruction *_popInstruction();
};

#endif // !AINSTRUCTION_BUS_CLIENT_HPP_

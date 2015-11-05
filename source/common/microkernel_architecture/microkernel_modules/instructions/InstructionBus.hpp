#ifndef INSTRUCTION_BUS_HPP_
# define INSTRUCTION_BUS_HPP_

# include <QThread>
# include <QMap>
# include <QQueue>
# include "AInstructionBusClient.hpp"
# include "AInstruction.hpp"

class InstructionBus
{
protected:
    QThread *_thread;
    QMap<AInstructionBusClient::eClientId, AInstructionBusClient *> _clientRegister;
    QMap<AInstructionBusClient *, QQueue<AInstruction *> *> _clientsInstructions;

public:
    InstructionBus(QThread *, QMap<AInstructionBusClient::eClientId, AInstructionBusClient *>,
                   QMap<AInstructionBusClient *, QQueue<AInstruction *> *>);
    virtual ~InstructionBus();

    void init();
    void run();
    void _register(AInstructionBusClient::eClientId, AInstructionBusClient *);
    void pushInstruction(AInstruction *);
    void _dispatchInstruction(AInstruction *);

    void setThread(QThread *);
    void setClientRegister(QMap<AInstructionBusClient::eClientId, AInstructionBusClient *>);
    void setClientsInstructions(QMap<AInstructionBusClient *, QQueue<AInstruction *> *>);

    QThread *getThread() const;
    QMap<AInstructionBusClient::eClientId, AInstructionBusClient *> getClientRegister() const;
    QMap<AInstructionBusClient *, QQueue<AInstruction *> *> getClientsInstructions() const;
};

#endif // !INSTRUCTION_BUS_HPP_

#ifndef INSTRUCTIONBUS_HPP_
#define INSTRUCTIONBUS_HPP_

# include <iostream>
# include <QThread>
# include <QMap>
# include <QQueue>
# include "AInstructionBusClient.hpp"
# include "AInstruction.hpp"

class InstructionBus
{
    public:
        InstructionBus(QThread *, QMap<AInstructionBusClient::eClientId, AInstructionBusClient *>,
                       QMap<AInstructionBusClient *, QQueue<AInstruction *> *>);
        virtual ~InstructionBus();
        QThread *getThread() const;
        void setThread(QThread *);
        QMap<AInstructionBusClient::eClientId, AInstructionBusClient *> getClientRegister() const;
        void setClientRegister(QMap<AInstructionBusClient::eClientId, AInstructionBusClient *>);
        QMap<AInstructionBusClient *, QQueue<AInstruction *> *> getClientsInstructions() const;
        void setClientsInstructions(QMap<AInstructionBusClient *, QQueue<AInstruction *> *>);

        void init();
        void run();
        void _register(AInstructionBusClient::eClientId, AInstructionBusClient *);
        void pushInstruction(AInstruction *);
        void _dispatchInstruction(AInstruction *);

    protected:
        QThread *_thread;
        QMap<AInstructionBusClient::eClientId, AInstructionBusClient *> _clientRegister;
        QMap<AInstructionBusClient *, QQueue<AInstruction *> *> _clientsInstructions;
};

#endif // INSTRUCTIONBUS_HPP_

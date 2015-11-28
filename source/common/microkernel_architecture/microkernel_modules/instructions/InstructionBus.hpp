#ifndef INSTRUCTION_BUS_HPP_
# define INSTRUCTION_BUS_HPP_

# include "AInstructionBusClient.hpp"
# include <QThread>
# include <QMutex>
# include <QQueue>
# include <QMap>

class InstructionBus : public QObject
{
    Q_OBJECT

private:
    QThread *_thread;
    QMutex *_mutex;
    QMap<AInstructionBusClient::eClientId, AInstructionBusClient *> _localClientsRegister;
    QMap<AInstructionBusClient *, QQueue<AInstruction *> *> _transmitterClientsInstructions;

public:
    explicit InstructionBus(QObject *parent = 0);
    ~InstructionBus();

    bool init();
    bool registerClient(AInstructionBusClient::eClientId, AInstructionBusClient *);
    bool pushInstruction(AInstruction *);

private slots:
    void _run();

private:
    void _dispatchInstruction(AInstruction *);
};

#endif // !INSTRUCTION_BUS_HPP_

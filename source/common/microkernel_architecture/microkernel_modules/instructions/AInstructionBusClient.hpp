#ifndef AINSTRUCTION_BUS_CLIENT_HPP_
# define AINSTRUCTION_BUS_CLIENT_HPP_

# include <QObject>
# include <QMutex>
# include <QQueue>

class AInstruction;

//
// Note: Override the onInstructionPushed() slot
// ONLY if the `AInstructionBusClient` is running on the main
// thread with a Qt event loop
//

class AInstructionBusClient : public QObject
{
    Q_OBJECT

public:
    enum eClientId : unsigned int
    {
        INVALID = 0,
        ALL = 1,

        NETWORK_MANAGER = 2,
        GUI = 3,
    };

private:
    QMutex _mutex;
    QQueue<AInstruction *> _instructions;
    bool _slotEnabled;

protected:
    eClientId _clientId;

public:
    AInstructionBusClient(eClientId clientId = INVALID);
    virtual ~AInstructionBusClient();

    void pushInstruction(AInstruction *);
    void enableInstructionPushedSlot();

    eClientId getClientId() const;
    bool instructionPushedSlotEnabled() const;

protected:
    AInstruction *_popInstruction();

private slots:
    virtual void onInstructionPushed();

signals:
    void instructionPushed();
};

#endif // !AINSTRUCTION_BUS_CLIENT_HPP_

#ifndef AINSTRUCTION_HPP_
# define AINSTRUCTION_HPP_

# include "AInstructionBusClient.hpp"

class AInstruction
{
protected:
    AInstructionBusClient *_transmitter;
    AInstructionBusClient::eClientId _receiver;
    int _instructionId;

public:
    AInstruction(AInstructionBusClient *, AInstructionBusClient::eClientId, int);
    AInstruction(const AInstruction &);
    virtual ~AInstruction();

    void setTransmitter(AInstructionBusClient *);
    void setReceiver(AInstructionBusClient::eClientId);
    void setInstructionId(int);

    AInstructionBusClient *getTransmitter() const;
    AInstructionBusClient::eClientId getReceiver() const;
    int getInstructionId() const;
};

#endif // !AINSTRUCTION_HPP_

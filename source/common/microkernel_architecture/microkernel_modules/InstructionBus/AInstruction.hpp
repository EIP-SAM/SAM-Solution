#ifndef AINSTRUCTION_HPP_
#define AINSTRUCTION_HPP_

# include "AInstructionBusClient.hpp"

class AInstruction
{
    public:
  AInstruction(AInstructionBusClient *, AInstructionBusClient::eClientId, int);
        virtual ~AInstruction();
        AInstructionBusClient *getTransmitter() const;
        void setTransmitter(AInstructionBusClient *);
        AInstructionBusClient::eClientId getReceiver() const;
        void setReceiver(AInstructionBusClient::eClientId);
        int getInstructionId() const;
        void setInstructionId(int);

    private:
        AInstructionBusClient *_transmitter;
        AInstructionBusClient::eClientId _receiver;
        int _instructionId;
};

#endif // !AINSTRUCTION_HPP_

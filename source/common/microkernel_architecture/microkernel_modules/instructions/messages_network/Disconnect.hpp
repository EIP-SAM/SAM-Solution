#ifndef DISCONNECT_HPP_
# define DISCONNECT_HPP_

# include "InstructionBuffer.hpp"

class Disconnect : public InstructionBuffer
{
private:
    static const unsigned int _INSTRUCTION_CODE;

private:
    void _initInstructionHeader(eProgId transmitterProgId,
				AInstructionBusClient::eClientId firstTransmitterId,
				AInstructionBusClient::eClientId finalReceiverId);
public:
    Disconnect(eProgId transmitterProgId,
	       AInstructionBusClient::eClientId firstTransmitterId,
	       AInstructionBusClient::eClientId finalReceiverId);
    Disconnect(Disconnect *disconnect);

    virtual ~Disconnect();
};

# ifdef __DISCONNECT_PRIVATE_DEF

const unsigned int Disconnect::_INSTRUCTION_CODE = 2;

# endif // !__DISCONNECT_PRIVATE_DEF

#endif // !DISCONNECT_HPP_

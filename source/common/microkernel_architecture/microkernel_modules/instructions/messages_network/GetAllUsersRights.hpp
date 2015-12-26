#ifndef GET_ALL_USERS_RIGHTS_HPP_
# define GET_ALL_USERS_RIGHTS_HPP_

# include "InstructionBuffer.hpp"

class GetAllUsersRights : public InstructionBuffer
{
private:
    static const unsigned int _INSTRUCTION_CODE;

private:
    void _initInstructionHeader(eProgId transmitterProgId,
				AInstructionBusClient::eClientId firstTransmitterId,
				AInstructionBusClient::eClientId finalReceiverId);

public:
    GetAllUsersRights(eProgId transmitterProgId,
		      AInstructionBusClient::eClientId firstTransmitterId,
		      AInstructionBusClient::eClientId finalReceiverId);
    GetAllUsersRights(GetAllUsersRights *getAllUsersRights);

    virtual ~GetAllUsersRights();
};

# ifdef __GET_ALL_USERS_RIGHTS_PRIVATE_DEF

const unsigned int GetAllUsersRights::_INSTRUCTION_CODE = 6;

# endif // !GET_ALL_USERS_RIGHTS_DEF

#endif // !GET_ALL_USERS_RIGHTS_HPP_

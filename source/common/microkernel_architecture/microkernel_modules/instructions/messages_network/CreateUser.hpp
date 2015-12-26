#ifndef CREATE_USER_HPP_
# define CREATE_USER_HPP_

# include "InstructionBuffer.hpp"
# include "InstructionQStringParameter.hpp"
# include "InstructionIntParameter.hpp"

class CreateUser : public InstructionBuffer
{
private:
    static const unsigned int _INSTRUCTION_CODE;
    static const unsigned int _SIZE_INTEGER;

private:
    QString _login;
    int _rights;

private:
    void _initInstructionHeader(eProgId transmitterProgId,
				AInstructionBusClient::eClientId firstTransmitterId,
				AInstructionBusClient::eClientId finalReceiverId);
    void _createParameterOfCreateUser();

public:
    CreateUser(const QString &login, int rights, eProgId transmitterProgId,
	       AInstructionBusClient::eClientId firstTransmitterId,
	       AInstructionBusClient::eClientId finalReceiverId);
    CreateUser(CreateUser *createUser);

    virtual ~CreateUser();

    QString getLogin() const;
    void setLogin(const QString &login);
    int getRights() const;
    void setRights(int rights);
};

# ifdef __CREATE_USER_PRIVATE_DEF

const unsigned int CreateUser::_INSTRUCTION_CODE = 7;
const unsigned int CreateUser::_SIZE_INTEGER = 4;

# endif // !CREATE_USER_PRIVATE_DEF

#endif // !CREATE_USER_HPP_

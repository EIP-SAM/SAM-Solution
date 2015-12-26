#ifndef CONNECT_HPP_
# define CONNECT_HPP_

# include "InstructionBuffer.hpp"
# include "InstructionQStringParameter.hpp"

class Connect : public InstructionBuffer
{
private:
    static const unsigned int _INSTRUCTION_CODE;

private:
    QString _login;
    QString _password;

private:
    void _initInstructionHeader(eProgId transmitterProgId,
				AInstructionBusClient::eClientId firstTransmitterId,
				AInstructionBusClient::eClientId finalReceiverId);
    void _createParameterOfConnect();

public:
    Connect(const QString &login, const QString &password, eProgId transmitterProgId,
	    AInstructionBusClient::eClientId firstTransmitterId,
	    AInstructionBusClient::eClientId finalReceiverId);
    Connect(Connect *co);

    virtual ~Connect();

    QString getLogin() const;
    void setLogin(const QString &login);
    QString getPassword() const;
    void setPassword(const QString &password);
};

# ifdef __CONNECT_PRIVATE_DEF

const unsigned int Connect::_INSTRUCTION_CODE = 1;

# endif // !__CONNECT_PRIVATE_DEF

#endif // !CONNECT_HPP_

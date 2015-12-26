#define __CONNECT_PRIVATE_DEF
#include "Connect.hpp"
#include "ReturnType.hpp"

//
// Constructor
//
Connect::Connect(const QString &login, const QString &password, eProgId transmitterProgid,
		 AInstructionBusClient::eClientId firstTransmitterId,
		 AInstructionBusClient::eClientId finalReceiverId)
{
    _initInstructionHeader(transmitterProgid, firstTransmitterId, finalReceiverId);
    _login = login;
    _password = password;
    _createParameterOfConnect();
}

//
// Copy constructor
//
Connect::Connect(Connect *co)
{
    _initInstructionHeader(co->getTransmitterProgId(), co->getFirstTransmitter(), co->getFinalReceiver());
    _login = co->getLogin();
    _password = co->getPassword();
    _createParameterOfConnect();
}

//
// Destructor
//
Connect::~Connect()
{
}

//
// Init all elements of the instruction's header
//
void Connect::_initInstructionHeader(eProgId transmitterProgid,
				     AInstructionBusClient::eClientId firstTransmitterId,
				     AInstructionBusClient::eClientId finalReceiverId)
{
    resetMagicNumber();
    setTransmitterProgId(transmitterProgid);
    setFirstTransmitter(firstTransmitterId);
    setFinalReceiver(finalReceiverId);
    setInstructionCode(_INSTRUCTION_CODE);
    setReturnType(ReturnType::BOOLEAN);
}

//
// Add parameters which compose connect message to `_data`
//
void Connect::_createParameterOfConnect()
{
    AInstruction::Parameter *loginParameter = createParameter(_login.size());
    AInstruction::QStringParameter *qStringLoginParameter = new AInstruction::QStringParameter(loginParameter->getAInstruction(), loginParameter->getHeader());
    qStringLoginParameter->setRawData(_login);

    AInstruction::Parameter *passwordParameter = createParameter(_password.size());
    AInstruction::QStringParameter *qStringPasswordParameter = new AInstruction::QStringParameter(passwordParameter->getAInstruction(), passwordParameter->getHeader());
    qStringPasswordParameter->setRawData(_password);
}

//
// Getter `_login`
//
QString Connect::getLogin() const
{
    return (_login);
}

//
// Setter `_login`
//
void Connect::setLogin(const QString &login)
{
    _login = login;
}

//
// Getter `_password`
//
QString Connect::getPassword() const
{
    return (_password);
}

//
// Setter `_password`
//
void Connect::setPassword(const QString &password)
{
    _password = password;
}

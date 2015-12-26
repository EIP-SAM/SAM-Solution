#define __CONNECT_PRIVATE_DEF
#include "Connect.hpp"
#include "ReturnType.hpp"
#include <string>
#include <iostream>

Connect::Connect(QString login, QString password, eProgId transmitterProgid,
		 AInstructionBusClient::eClientId firstTransmitterId,
		 AInstructionBusClient::eClientId finalReceiverId)
{
    _initInstructionHeader(transmitterProgid, firstTransmitterId, finalReceiverId);
    _login = login;
    _password = password;
    _createParameterOfConnect();
}

Connect::Connect(Connect *co)
{
    _initInstructionHeader(co->getTransmitterProgId(), co->getFirstTransmitter(), co->getFinalReceiver());
    _login = co->getLogin();
    _password = co->getPassword();
    _createParameterOfConnect();
}

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

void Connect::_createParameterOfConnect()
{
    AInstruction::Parameter *loginParameter = createParameter(_login.size());
    AInstruction::QStringParameter *qStringLoginParameter = new AInstruction::QStringParameter(loginParameter->getAInstruction(), loginParameter->getHeader());
    qStringLoginParameter->setRawData(_login);

    AInstruction::Parameter *passwordParameter = createParameter(_password.size());
    AInstruction::QStringParameter *qStringPasswordParameter = new AInstruction::QStringParameter(passwordParameter->getAInstruction(), passwordParameter->getHeader());
    qStringPasswordParameter->setRawData(_password);
}

Connect::~Connect()
{
}

QString Connect::getLogin() const
{
    return (_login);
}

void Connect::setLogin(QString login)
{
    _login = login;
}

QString Connect::getPassword() const
{
    return (_password);
}

void Connect::setPassword(QString password)
{
    _password = password;
}

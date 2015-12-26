#define __CREATE_USER_PRIVATE_DEF
#include "CreateUser.hpp"
#include "ReturnType.hpp"

//
// Constructor
//
CreateUser::CreateUser(const QString &login, int rights, eProgId transmitterProgId,
	   AInstructionBusClient::eClientId firstTransmitterId,
	   AInstructionBusClient::eClientId finalReceiverId)
{
    _initInstructionHeader(transmitterProgId, firstTransmitterId, finalReceiverId);
    _login = login;
    _rights = rights;
    _createParameterOfCreateUser();
}

//
// Copy constructor
//
CreateUser::CreateUser(CreateUser *createUser)
{
    _initInstructionHeader(createUser->getTransmitterProgId(), createUser->getFirstTransmitter(),
			   createUser->getFinalReceiver());
    _login = createUser->getLogin();
    _rights = createUser->getRights();
    _createParameterOfCreateUser();
}

//
// Destructor
//
CreateUser::~CreateUser()
{
}

//
// Init all elements of the instruction's header
//
void CreateUser::_initInstructionHeader(eProgId transmitterProgid,
					AInstructionBusClient::eClientId firstTransmitterId,
					AInstructionBusClient::eClientId finalReceiverId)
{
    resetMagicNumber();
    setTransmitterProgId(transmitterProgid);
    setFirstTransmitter(firstTransmitterId);
    setFinalReceiver(finalReceiverId);
    setInstructionCode(_INSTRUCTION_CODE);
    setReturnType(ReturnType::QSTRING);
}

//
// Add parameters which compose connect message to `_data`
//
void CreateUser::_createParameterOfCreateUser()
{
    AInstruction::Parameter *loginParameter = createParameter(_login.size());
    AInstruction::QStringParameter *qStringLoginParameter = new AInstruction::QStringParameter(loginParameter->getAInstruction(), loginParameter->getHeader());
    qStringLoginParameter->setRawData(_login);

    AInstruction::Parameter *rightsParameter = createParameter(_SIZE_INTEGER);
    AInstruction::IntParameter *intRightsParameter = new AInstruction::IntParameter(rightsParameter->getAInstruction(), rightsParameter->getHeader());
    intRightsParameter->setRawData(_rights);
}

//
// Getter `_login`
//
QString CreateUser::getLogin() const
{
    return (_login);
}

//
// Setter `_login`
//
void CreateUser::setLogin(const QString &login)
{
    _login = login;
}

//
// Getter `_rights`
//
int CreateUser::getRights() const
{
    return (_rights);
}

//
// Setter `_rights`
//
void CreateUser::setRights(int rights)
{
    _rights = rights;
}

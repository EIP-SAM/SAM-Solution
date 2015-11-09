#include "AInstruction.hpp"

//
// See notes in header file for a description of these static members
//
const magicNumber_t AInstruction::_MAGIC_NUMBER = 0x10101042;
const int AInstruction::_INSTRUCTION_HEADER_SIZE = sizeof(AInstruction::instructionHeader_t);
const int AInstruction::_FIRST_PARAMETER_OFFSET = _INSTRUCTION_HEADER_SIZE;
const int AInstruction::_INSTRUCTION_PARAMETER_HEADER_SIZE = sizeof(AInstruction::instructionParameterHeader_t);
const int AInstruction::_PARAMETER_DATA_OFFSET = _INSTRUCTION_PARAMETER_HEADER_SIZE;

AInstruction::AInstruction()
    : _data(_INSTRUCTION_HEADER_SIZE, 0)
{
    _setPointersToData();
}

AInstruction::AInstruction(const AInstruction &o)
    : _data(o._data), _localTransmitter(o._localTransmitter)
{
    _setPointersToData();
}

AInstruction::AInstruction(const QByteArray &data)
    : _data(data)
{
    _ensureMinimumDataSize();
    _setPointersToData();
}

AInstruction::~AInstruction()
{
}

void AInstruction::setRawData(const QByteArray &rawData)
{
    _data = rawData;
    _ensureMinimumDataSize();
    _setPointersToData();
}

void AInstruction::setLocalTransmitter(AInstructionBusClient *localTransmitter)
{
    _localTransmitter = localTransmitter;
}

void AInstruction::resetMagicNumber()
{
    _header->magicNumber = _MAGIC_NUMBER;
}

void AInstruction::setFirstTransmitter(AInstructionBusClient::eClientId firstTransmitter)
{
    _header->firstTransmitterId = firstTransmitter;
}

void AInstruction::setFinalReceiver(AInstructionBusClient::eClientId finalReceiver)
{
    _header->finalReceiverId = finalReceiver;
}

void AInstruction::setInstructionCode(unsigned int instructionCode)
{
    _header->instructionCode = instructionCode;
}

void AInstruction::setReturnType(unsigned int returnType)
{
    _header->returnType = returnType;
}

void AInstruction::setNumberOfParameters(unsigned int n)
{
    _header->numberOfParameters = n;
}

void AInstruction::appendParameter(unsigned int parameterType,
                                   unsigned int parameterSize,
                                   const void *rawParameterData)
{
    (void)parameterType;
    (void)parameterSize;
    (void)rawParameterData;
}

const QByteArray &AInstruction::getRawData() const
{
    return _data;
}

const AInstructionBusClient *AInstruction::getLocalTransmitter() const
{
    return _localTransmitter;
}

bool AInstruction::isMagicNumberValid() const
{
    return _header->magicNumber == _MAGIC_NUMBER;
}

AInstructionBusClient::eClientId AInstruction::getFirstTransmitter() const
{
    return _header->firstTransmitterId;
}

AInstructionBusClient::eClientId AInstruction::getFinalReceiver() const
{
    return _header->finalReceiverId;
}

unsigned int AInstruction::getInstructionCode() const
{
    return _header->instructionCode;
}

unsigned int AInstruction::getReturnType() const
{
    return _header->returnType;
}

unsigned int AInstruction::getNumberOfParameters() const
{
    return _header->numberOfParameters;
}

unsigned int AInstruction::getParameterNumber(unsigned int n, void *&data) const
{
    (void)n;
    (void)data;
    return 0; // size of param
}

void AInstruction::_ensureMinimumDataSize(int minSize)
{
    if (_data.size() < minSize)
        _data.append(QByteArray(minSize - _data.size(), 0));
}

//
// Note: Do not check if `_data` is big enough
//
void AInstruction::_setPointersToData()
{
    char *data = _data.data();

    _header = (instructionHeader_t *)data;
    _parametersData = _header->numberOfParameters == 0 ? NULL : (void *)(&data[_FIRST_PARAMETER_OFFSET]);
}

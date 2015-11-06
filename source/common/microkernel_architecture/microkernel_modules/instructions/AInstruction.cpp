#include "AInstruction.hpp"
#include <cstddef>

//
// See notes in header file for a description of these static members
//
const magicNumber_t AInstruction::_MAGIC_NUMBER = 0x10101042;

const std::size_t AInstruction::_INSTRUCTION_HEADER_SIZE = sizeof(AInstruction::instructionHeader_t);
const std::size_t AInstruction::_MAGIC_NUMBER_OFFSET = offsetof(AInstruction::instructionHeader_t, magicNumber);
const std::size_t AInstruction::_FIRST_TRANSMITTER_ID_OFFSET = offsetof(AInstruction::instructionHeader_t, firstTransmitterId);
const std::size_t AInstruction::_FINAL_RECEIVER_ID_OFFSET = offsetof(AInstruction::instructionHeader_t, finalReceiverId);
const std::size_t AInstruction::_INSTRUCTION_CODE_OFFSET = offsetof(AInstruction::instructionHeader_t, instructionCode);
const std::size_t AInstruction::_RETURN_TYPE_OFFSET = offsetof(AInstruction::instructionHeader_t, returnType);
const std::size_t AInstruction::_NUMBER_OF_PARAMETERS_OFFSET = offsetof(AInstruction::instructionHeader_t, numberOfParameters);
const std::size_t AInstruction::_FIRST_PARAMETER_OFFSET = _INSTRUCTION_HEADER_SIZE;

const std::size_t AInstruction::_INSTRUCTION_PARAMETER_HEADER_SIZE = sizeof(AInstruction::instructionParameterHeader_t);
const std::size_t AInstruction::_PARAMETER_TYPE_OFFSET = offsetof(AInstruction::instructionParameterHeader_t, parameterType);
const std::size_t AInstruction::_PARAMETER_SIZE_OFFSET = offsetof(AInstruction::instructionParameterHeader_t, parameterSize);
const std::size_t AInstruction::_PARAMETER_DATA_OFFSET = _INSTRUCTION_PARAMETER_HEADER_SIZE;

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
    *_magicNumber = _MAGIC_NUMBER;
}

void AInstruction::setFirstTransmitter(AInstructionBusClient::eClientId firstTransmitter)
{
    *_firstTransmitterId = firstTransmitter;
}

void AInstruction::setFinalReceiver(AInstructionBusClient::eClientId finalReceiver)
{
    *_finalReceiverId = finalReceiver;
}

void AInstruction::setInstructionCode(unsigned int instructionCode)
{
    *_instructionCode = instructionCode;
}

void AInstruction::setReturnType(unsigned int returnType)
{
    *_returnType = returnType;
}

void AInstruction::setNumberOfParameters(unsigned int n)
{
    *_numberOfParameters = n;
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
    return *_magicNumber == _MAGIC_NUMBER;
}

AInstructionBusClient::eClientId AInstruction::getFirstTransmitter() const
{
    return *_firstTransmitterId;
}

AInstructionBusClient::eClientId AInstruction::getFinalReceiver() const
{
    return *_finalReceiverId;
}

unsigned int AInstruction::getInstructionCode() const
{
    return *_instructionCode;
}

unsigned int AInstruction::getReturnType() const
{
    return *_returnType;
}

unsigned int AInstruction::getNumberOfParameters() const
{
    return *_numberOfParameters;
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
// Make the attributes pointing to the corresponding data of `_data`
// Do not check if `_data` is big enough
//
void AInstruction::_setPointersToData()
{
    char *data = _data.data();

    _magicNumber = (magicNumber_t *)(&data[_MAGIC_NUMBER_OFFSET]);
    _firstTransmitterId = (AInstructionBusClient::eClientId *)(&data[_FIRST_TRANSMITTER_ID_OFFSET]);
    _finalReceiverId = (AInstructionBusClient::eClientId *)(&data[_FINAL_RECEIVER_ID_OFFSET]);
    _instructionCode = (unsigned int *)(&data[_INSTRUCTION_CODE_OFFSET]);
    _returnType = (unsigned int *)(&data[_RETURN_TYPE_OFFSET]);
    _numberOfParameters = (unsigned int *)(&data[_NUMBER_OF_PARAMETERS_OFFSET]);
    _parametersData = *_numberOfParameters == 0 ? NULL : (void *)(&data[_FIRST_PARAMETER_OFFSET]);
}

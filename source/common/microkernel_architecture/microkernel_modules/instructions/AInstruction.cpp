#include "AInstruction.hpp"

#include <QDebug>

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
    _setPointerToData();
}

AInstruction::AInstruction(const AInstruction &o)
    : _data(o._data), _localTransmitter(o._localTransmitter)
{
    _setPointerToData();
}

AInstruction::AInstruction(const QByteArray &data)
    : _data(data)
{
    _ensureMinimumDataSize();
    _setPointerToData();
}

AInstruction::~AInstruction()
{
}

void AInstruction::setRawData(const QByteArray &rawData)
{
    _data = rawData;
    _ensureMinimumDataSize();
    _setPointerToData();
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

//
AInstruction::Parameter *AInstruction::createParameter(int size)
{
    instructionParameterHeader_t *paramHeader = NULL;
    Parameter *parameter = NULL;
    int paramHeaderOffset = _data.size();

    _data.append(QByteArray(_INSTRUCTION_PARAMETER_HEADER_SIZE + size, 0));
    _setPointerToData();
    paramHeader = (instructionParameterHeader_t *)(((char *)_header) + paramHeaderOffset);
    if (!(parameter = new (std::nothrow) Parameter(*this, paramHeader)))
    {
        _data.resize(paramHeaderOffset);
        _setPointerToData();
        return NULL;
    }
    ++_header->numberOfParameters;
    paramHeader->parameterSize = size;
    _parameters << parameter;
    return parameter;
}

//
// delete in list + in raw data
// -- nb params
//
void AInstruction::deleteParameterNumber(int n)
{
    instructionParameterHeader_t *parameterHeader = NULL;
    QByteArray newData;

    if (!n || _parameters.size() < n)
        return ;
    parameterHeader = _parameters[n - 1]->getHeader();
    newData.append(_data.left(((char *)parameterHeader) - ((char *)_header)));
    newData.append(_data.right(((char *)parameterHeader) - ((char *)_header) + _INSTRUCTION_PARAMETER_HEADER_SIZE + parameterHeader->parameterSize));
    delete _parameters[n - 1];
    _parameters.removeAt(n - 1);
    _data = newData;
    _resetPointersToParameters();
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

int AInstruction::getNumberOfParameters() const
{
    return _header->numberOfParameters;
}

//
AInstruction::Parameter *AInstruction::getParameterNumber(int n) const
{
    if (!n || n > _parameters.size() || n > _header->numberOfParameters)
        return NULL;
    return _parameters[n - 1];
}

//
AInstruction::instructionParameterHeader_t *AInstruction::_getParameterNumber(int n) const
{
    Parameter *parameter = getParameterNumber(n);

    if (parameter)
        return parameter->getHeader();
    return NULL;
}

void AInstruction::_ensureMinimumDataSize(int minSize)
{
    if (_data.size() < minSize)
        _data.append(QByteArray(minSize - _data.size(), 0));
}

//
// Note: Do not check if `_data` is big enough
//
inline void AInstruction::_setPointerToData()
{
    _header = (instructionHeader_t *)_data.data();
}

//
bool AInstruction::_parameterIsValid(instructionParameterHeader_t *parameterHeader)
{
    instructionParameterHeader_t *parameterHeaderCmp = NULL;
    unsigned int paramN = 1;

    if (!parameterHeader)
        return false;
    while (parameterHeader != (parameterHeaderCmp = _getParameterNumber(paramN++)) && parameterHeaderCmp);
    return parameterHeaderCmp && parameterHeader == parameterHeaderCmp;
}

//
// Resize the parameter if possible
// Reset data pointers in all `AInstruction::Parameter` instanciated in
// `_parameters`
//
void AInstruction::_resizeParameter(instructionParameterHeader_t *parameterHeader, int size)
{
    int endParameterOffset = 0;

    if (_parameterIsValid(parameterHeader) && size != parameterHeader->parameterSize)
    {
        QByteArray newData(_data.left(((char *)parameterHeader) - ((char *)_header)));

        if (size > parameterHeader->parameterSize)
        {
            newData.append((char *)parameterHeader, _INSTRUCTION_PARAMETER_HEADER_SIZE + parameterHeader->parameterSize);
            newData.append(QByteArray(size - parameterHeader->parameterSize, 0));
        }
        else
            newData.append((char *)parameterHeader, _INSTRUCTION_PARAMETER_HEADER_SIZE + size);
        endParameterOffset = (((char *)parameterHeader) + _INSTRUCTION_PARAMETER_HEADER_SIZE + parameterHeader->parameterSize) - ((char *)_header);
        if (_data.size() > endParameterOffset)
            newData.append(_data.mid(endParameterOffset));
        ((instructionParameterHeader_t *)(newData.data() + (((char *)parameterHeader) - ((char *)_header))))->parameterSize = size;
        _data = newData;
        _resetPointersToParameters();
    }
}

void AInstruction::_resetPointersToParameters()
{
    instructionParameterHeader_t *paramHeader = NULL;
    int i = 0, paramHeaderOffset = _FIRST_PARAMETER_OFFSET;

    _setPointerToData();
    while (paramHeaderOffset < _data.size())
    {
        paramHeader = (instructionParameterHeader_t *)(((char *)_header) + paramHeaderOffset);
        _parameters[i++]->setHeader(paramHeader);
        paramHeaderOffset += _INSTRUCTION_PARAMETER_HEADER_SIZE + paramHeader->parameterSize;
    }
}

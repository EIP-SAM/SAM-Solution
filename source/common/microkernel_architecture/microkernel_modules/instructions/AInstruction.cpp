#include "AInstruction.hpp"

//
// See notes in header file for a description of these static members
//
const magicNumber_t AInstruction::_MAGIC_NUMBER = 0x10101042;
const int AInstruction::_INSTRUCTION_HEADER_SIZE = sizeof(AInstruction::instructionHeader_t);
const int AInstruction::_FIRST_PARAMETER_OFFSET = _INSTRUCTION_HEADER_SIZE;
const int AInstruction::_INSTRUCTION_PARAMETER_HEADER_SIZE = sizeof(AInstruction::instructionParameterHeader_t);
const int AInstruction::_PARAMETER_DATA_OFFSET = _INSTRUCTION_PARAMETER_HEADER_SIZE;

//
// Construct a byte array of the size an instruction header, filled of 0
//
AInstruction::AInstruction()
    : _data(_INSTRUCTION_HEADER_SIZE, 0)
{
    _setPointerToData();
}

//
// Initialize a copy of the instruction
//
AInstruction::AInstruction(const AInstruction &o)
    : _data(o._data), _localTransmitter(o._localTransmitter)
{
    _setPointerToData();
    // copy parameters
}

//
// Initialize the instruction data with the given byte array
// The byte array is enlarged if it doesn't have at least the size of
// an instruction header
//
AInstruction::AInstruction(const QByteArray &data)
    : _data(data)
{
    _ensureMinimumDataSize();
    _setPointerToData();
}

//
// Delete parameters
//
AInstruction::~AInstruction()
{
    for (auto parameter : _parameters)
        delete parameter;
}

//
// Setter: Set local instruction bus client transmiter
//
void AInstruction::setLocalTransmitter(AInstructionBusClient *localTransmitter)
{
    _localTransmitter = localTransmitter;
}

//
// Setter: Reset magic number
//
void AInstruction::resetMagicNumber()
{
    _header->magicNumber = _MAGIC_NUMBER;
}

//
// Setter: Set first instruction bus client transmitter id
//
void AInstruction::setFirstTransmitter(AInstructionBusClient::eClientId firstTransmitter)
{
    _header->firstTransmitterId = firstTransmitter;
}

//
// Setter: Set final instruction bus client receiver id
//
void AInstruction::setFinalReceiver(AInstructionBusClient::eClientId finalReceiver)
{
    _header->finalReceiverId = finalReceiver;
}

//
// Setter: Set instruction code
// Note: Supposed to be an enum in an instruction bus client subclass
//   One enum for one client - so one functionality - is supposed to be
//   created, representing its own instructions
//
void AInstruction::setInstructionCode(unsigned int instructionCode)
{
    _header->instructionCode = instructionCode;
}

//
// Setter: Set instruction return type
//
void AInstruction::setReturnType(unsigned int returnType)
{
    // An AInstruction::eReturnType should be used instead
    _header->returnType = returnType;
}

//
// Create a new parameter
// `_data` is extented of at least the size of an instruction parameter header
// A new `Parameter *` is created and pushed in the `_parameters` list
//
AInstruction::Parameter *AInstruction::createParameter(int size)
{
    instructionParameterHeader_t *paramHeader = NULL;
    Parameter *parameter = NULL;
    int paramHeaderOffset = _data.size();

    if (size < 0)
        return NULL;
    _data.append(QByteArray(_INSTRUCTION_PARAMETER_HEADER_SIZE + size, 0));
    _resetPointersToParameters();
    paramHeader = (instructionParameterHeader_t *)(((char *)_header) + paramHeaderOffset);
    if (!(parameter = new (std::nothrow) Parameter(*this, paramHeader)))
    {
        _data.resize(paramHeaderOffset);
        _resetPointersToParameters();
        return NULL;
    }
    ++_header->numberOfParameters;
    paramHeader->parameterSize = size;
    _parameters << parameter;
    return parameter;
}

//
// Delete the n'th parameter in `_parameters` and in `_data`
// Note: Index `n` starts at 1
//
void AInstruction::deleteParameterNumber(int n)
{
    instructionParameterHeader_t *parameterHeader = NULL;
    QByteArray newData;

    if (n <= 0 || _parameters.size() < n)
        return ;
    n -= 1;
    parameterHeader = _parameters[n]->getHeader();
    newData.append(_data.left(((char *)parameterHeader) - ((char *)_header)));
    newData.append(_data.mid(((char *)parameterHeader) - ((char *)_header) +
                             _INSTRUCTION_PARAMETER_HEADER_SIZE + parameterHeader->parameterSize));
    delete _parameters[n];
    _parameters.removeAt(n);
    _data = newData;
    _resetPointersToParameters();
    --_header->numberOfParameters;
}

//
// Getter: Return local instruction bus client transmitter
//
const AInstructionBusClient *AInstruction::getLocalTransmitter() const
{
    return _localTransmitter;
}

//
// Getter: Return `true` if the current magic number is valid
//
bool AInstruction::isMagicNumberValid() const
{
    return _header->magicNumber == _MAGIC_NUMBER;
}

//
// Getter: Return the first instruction bus client transmitter id
//
AInstructionBusClient::eClientId AInstruction::getFirstTransmitter() const
{
    return _header->firstTransmitterId;
}

//
// Getter: Return the final instruction bus client receiver id
//
AInstructionBusClient::eClientId AInstruction::getFinalReceiver() const
{
    return _header->finalReceiverId;
}

//
// Getter: Return the instruction code
//
unsigned int AInstruction::getInstructionCode() const
{
    return _header->instructionCode;
}

//
// Getter: Return the instruction return type
//
unsigned int AInstruction::getReturnType() const
{
    return _header->returnType;
}

//
// Getter: Return the number of parameters of the instruction
//
int AInstruction::getNumberOfParameters() const
{
    return _header->numberOfParameters;
}

//
// Getter: Return the parameter number `n`
// Note: Index `n` starts at 1
//
AInstruction::Parameter *AInstruction::getParameterNumber(int n) const
{
    return (n <= 0 || n > _parameters.size() || n > _header->numberOfParameters) ? NULL : _parameters[n - 1];
}

//
// Getter: Return the header pointer of the parameter number `n`
// Note: Index `n` starts at 1
//
AInstruction::instructionParameterHeader_t *AInstruction::_getParameterNumber(int n) const
{
    Parameter *parameter = getParameterNumber(n);

    return parameter ? parameter->getHeader() : NULL;
}

//
// `minSize` default value is the size of an instruction header
// If the current `_data` size is not of the required size,
// `_data` is enlarged with additionals `0`
//
void AInstruction::_ensureMinimumDataSize(int minSize)
{
    if (_data.size() < minSize)
        _data.append(QByteArray(minSize - _data.size(), 0));
}

//
// Reset instruction header pointer with new `_data` byte array
//
inline void AInstruction::_setPointerToData()
{
    _header = (instructionHeader_t *)_data.data();
}

//
// Iterate over parameters to find if `parameterHeader` is a valid pointer
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
// Resize the instruction parameter
//
void AInstruction::_resizeParameter(instructionParameterHeader_t *parameterHeader, int size)
{
    int endParameterOffset = 0;

    if (size >= 0 && size != parameterHeader->parameterSize && _parameterIsValid(parameterHeader))
    {
        QByteArray newData(_data.left(((char *)parameterHeader) - ((char *)_header)));

        if (size > parameterHeader->parameterSize)
        {
            newData.append((char *)parameterHeader,
                           _INSTRUCTION_PARAMETER_HEADER_SIZE + parameterHeader->parameterSize);
            newData.append(QByteArray(size - parameterHeader->parameterSize, 0));
        }
        else
            newData.append((char *)parameterHeader, _INSTRUCTION_PARAMETER_HEADER_SIZE + size);
        endParameterOffset = (((char *)parameterHeader) - ((char *)_header)
                              + _INSTRUCTION_PARAMETER_HEADER_SIZE + parameterHeader->parameterSize);
        if (_data.size() > endParameterOffset)
            newData.append(_data.mid(endParameterOffset));
        parameterHeader = (instructionParameterHeader_t *)(newData.data() + (((char *)parameterHeader) - ((char *)_header)));
        parameterHeader->parameterSize = size;
        _data = newData;
        _resetPointersToParameters();
    }
}

//
// Reset pointers to header and parameter headers when `_data` is changed
//
void AInstruction::_resetPointersToParameters()
{
    instructionParameterHeader_t *paramHeader = NULL;
    int i = 0, paramHeaderOffset = _FIRST_PARAMETER_OFFSET;

    _setPointerToData();
    while (paramHeaderOffset < _data.size() && i != _parameters.size())
    {
        paramHeader = (instructionParameterHeader_t *)(((char *)_header) + paramHeaderOffset);
        _parameters[i++]->setHeader(paramHeader);
        paramHeaderOffset += _INSTRUCTION_PARAMETER_HEADER_SIZE + paramHeader->parameterSize;
    }
}

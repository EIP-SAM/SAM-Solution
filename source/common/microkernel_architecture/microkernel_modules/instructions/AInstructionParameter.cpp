#include "AInstruction.hpp"
#include "AInstructionParameter.hpp"

//
// Constructor
//
AInstruction::Parameter::Parameter(AInstruction &parent, instructionParameterHeader_t *header)
    : _parent(parent), _header(header)
{
}

//
// Destructor
//
AInstruction::Parameter::~Parameter()
{
}

//
// Setter: `header`
//
void AInstruction::Parameter::setHeader(instructionParameterHeader_t *header)
{
    _header = header;
}

//
// Setter: raw data `_data`
//
void AInstruction::Parameter::setRawData(const QByteArray& data)
{
    char *rawData = NULL;
    int i = -1;

    if (!isValid())
        return ;
    _parent._resizeParameter(_header, data.size());
    rawData = ((char *)_header) + _PARAMETER_DATA_OFFSET;
    while (++i != data.size())
        rawData[i] = data[i];
}

//
// Setter: append raw data to `_data`
//
void AInstruction::Parameter::appendRawData(const QByteArray& data)
{
    char *rawData = NULL;
    int i = -1;

    if (!isValid())
        return ;
    _parent._resizeParameter(_header, _header->parameterSize + data.size());
    i += _header->parameterSize;
    rawData = ((char *)_header) + _PARAMETER_DATA_OFFSET;
    while (++i != data.size())
        rawData[i] = data[i];
}

//
// Setter: parameter type
//
void AInstruction::Parameter::setType(unsigned int type)
{
    if (!isValid())
        return ;
    _header->parameterType = type;
}

//
// Setter: parameter size
//
void AInstruction::Parameter::setSize(int size)
{
    if (!isValid())
        return ;
    _parent._resizeParameter(_header, size);
    _header->parameterSize = size;
}

//
// Getter: `_header`
//
AInstruction::instructionParameterHeader_t *AInstruction::Parameter::getHeader() const
{
    return _header;
}


//
// Getter: `_parent`
//
AInstruction &AInstruction::Parameter::getAInstruction() const
{
    return _parent;
}

//
// Getter: parameter is valid
//
bool AInstruction::Parameter::isValid() const
{
    return _parent._parameterIsValid(_header);
}

//
// Getter: `_data`
//
QByteArray AInstruction::Parameter::getRawData() const
{
    QByteArray rawData;

    if (isValid())
        rawData.append(&((char *)_header)[_PARAMETER_DATA_OFFSET], _header->parameterSize);
    return rawData;
}

//
// Getter: parameter type
//
unsigned int AInstruction::Parameter::getType() const
{
    return isValid() ? _header->parameterType : (unsigned int)-1;
}

//
// Getter: parameter size
//
int AInstruction::Parameter::getSize() const
{
    return isValid() ? _header->parameterSize : -1;
}

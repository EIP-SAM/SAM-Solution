#include "AInstruction.hpp"
#include "AInstructionParameter.hpp"

AInstruction::Parameter::Parameter(AInstruction &parent, instructionParameterHeader_t *header)
    : _parent(parent), _header(header)
{
}

AInstruction::Parameter::~Parameter()
{
}

void AInstruction::Parameter::setHeader(instructionParameterHeader_t *header)
{
    _header = header;
}

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

void AInstruction::Parameter::setType(unsigned int type)
{
    if (!isValid())
        return ;
    _header->parameterType = type;
}

void AInstruction::Parameter::setSize(int size)
{
    if (!isValid())
        return ;
    _parent._resizeParameter(_header, size);
    _header->parameterSize = size;
}

AInstruction::instructionParameterHeader_t *AInstruction::Parameter::getHeader() const
{
    return _header;
}

bool AInstruction::Parameter::isValid() const
{
    return _parent._parameterIsValid(_header);
}

QByteArray AInstruction::Parameter::getRawData() const
{
    QByteArray rawData;

    if (isValid())
        rawData.append(&((char *)_header)[_PARAMETER_DATA_OFFSET], _header->parameterSize);
    return rawData;
}

unsigned int AInstruction::Parameter::getType() const
{
    return isValid() ? _header->parameterType : (unsigned int)-1;
}

int AInstruction::Parameter::getSize() const
{
    return isValid() ? _header->parameterSize : -1;
}

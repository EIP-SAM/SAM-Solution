#include "InstructionQStringParameter.hpp"
#include "ReturnType.hpp"

//
// Constructor
//
AInstruction::QStringParameter::QStringParameter(AInstruction &instruction, instructionParameterHeader_t *header)
    : Parameter(instruction, header)
{
    setType(ReturnType::QSTRING);
}

//
// Destructor
//
AInstruction::QStringParameter::~QStringParameter()
{
}

//
// Setter: raw data `_data`
//
void AInstruction::QStringParameter::setRawData(QString &data)
{
    char *rawData = NULL;
    std::string toChar = data.toStdString();
    unsigned int i = -1;
    unsigned int sizeData = data.size();

    setSize(sizeData);
    if (!isValid())
        return ;
    _parent._resizeParameter(_header, sizeData);
    rawData = ((char *)_header) + _PARAMETER_DATA_OFFSET;
    while (++i != sizeData)
        rawData[i] = toChar[i];
}

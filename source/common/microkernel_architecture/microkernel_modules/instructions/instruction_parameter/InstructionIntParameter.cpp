#define __INSTRUCTION_INT_PARAMETER_PRIVATE_DEF
#include "InstructionIntParameter.hpp"
#include "ReturnType.hpp"
#include <string>

//
// Constructor
//
AInstruction::IntParameter::IntParameter(AInstruction &instruction, instructionParameterHeader_t *header)
    : Parameter(instruction, header)
{
    setType(ReturnType::INTEGER);
    setSize(_SIZE);
}

//
// Destructor
//
AInstruction::IntParameter::~IntParameter()
{
}

//
// Setter: raw data `_data`
//
void AInstruction::IntParameter::setRawData(int data)
{
    char *rawData = NULL;
    std::string toChar;
    int i = -1;

    if (!isValid())
        return ;
    _parent._resizeParameter(_header, _SIZE);
    rawData = ((char *)_header) + _PARAMETER_DATA_OFFSET;
    toChar = std::to_string(data);
    while (++i != _SIZE)
        rawData[i] = toChar[i];
}

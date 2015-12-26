#ifndef INSTRUCTION_QSTRING_PARAMETER_HPP_
# define INSTRUCTION_QSTRING_PARAMETER_HPP_

#include "AInstructionParameter.hpp"

class AInstruction::QStringParameter : public AInstruction::Parameter
{
public:
    QStringParameter(AInstruction &, instructionParameterHeader_t *);
    virtual ~QStringParameter();

    void setRawData(QString &data);
};

#endif // !INSTRUCTION_QSTRING_PARAMETER_HPP_

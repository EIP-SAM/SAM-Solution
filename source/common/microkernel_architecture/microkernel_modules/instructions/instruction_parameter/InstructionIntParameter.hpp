#ifndef INSTRUCTION_INT_PARAMETER_HPP_
# define INSTRUCTION_INT_PARAMETER_HPP_

# include "AInstructionParameter.hpp"

class AInstruction::IntParameter : public AInstruction::Parameter
{
private:
    static const int _SIZE;

public:
    IntParameter(AInstruction &, instructionParameterHeader_t *);
    virtual ~IntParameter();

    void setRawData(int data);
};

#ifdef __INSTRUCTION_INT_PARAMETER_PRIVATE_DEF

const int AInstruction::IntParameter::_SIZE = 4;

# endif // !__INSTRUCTION_INT_PARAMETER_PRIVATE_DEF

#endif // !INSTRUCTION_INT_PARAMETER_HPP_

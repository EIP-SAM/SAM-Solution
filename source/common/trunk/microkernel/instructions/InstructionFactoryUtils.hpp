#ifndef INSTRUCTION_FACTORY_UTILS_HPP_
# define INSTRUCTION_FACTORY_UTILS_HPP_

# include "AInstructionModel.hpp"

class InstructionFactoryUtils
{
public:
  InstructionFactoryUtils();
  ~InstructionFactoryUtils();

  static AInstructionModel create(int instructionCode, int returnType, bool isSynchrone);
  static AInstructionModel create(QByteArray *byteArray);
  
};

#endif // !INSTRUCTION_FACTORY_UTILS_HPP_

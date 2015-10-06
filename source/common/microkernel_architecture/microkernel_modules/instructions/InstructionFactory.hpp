#ifndef INSTRUCTION_FACTORY_HPP_
# define INSTRUCTION_FACTORY_HPP_

# include "AInstructionModel.hpp"

class InstructionFactory
{
public:
  InstructionFactory();
  ~InstructionFactory();

  static AInstructionModel create(int instructionCode, int returnType, bool isSynchrone);
  static AInstructionModel create(QByteArray *byteArray);
  
};

#endif // !INSTRUCTION_FACTORY_HPP_

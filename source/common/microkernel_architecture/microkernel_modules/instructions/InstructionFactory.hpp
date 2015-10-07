#ifndef INSTRUCTION_FACTORY_HPP_
# define INSTRUCTION_FACTORY_HPP_

# include "ANetworkInstruction.hpp"

class InstructionFactory
{
public:
  InstructionFactory();
  ~InstructionFactory();

  static ANetworkInstruction create(int instructionCode, int returnType, bool isSynchrone);
  static ANetworkInstruction create(QByteArray *byteArray);

};

#endif // !INSTRUCTION_FACTORY_HPP_

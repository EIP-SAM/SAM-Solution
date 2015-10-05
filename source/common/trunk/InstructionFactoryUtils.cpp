#include "InstructionFactory.hpp"

//
// Create a message header with the instruction code, return type and synchrone parameters
//

InstructionFactoryUtils:AInstructionModel	create(int argInstructionCode, int argReturnType, bool argIsSynchrone)
{
  AInstructionModel				instructionModel;

  instructionModel.setInstructionCode(argInstrucitonCode);
  instructionModel.setReturnType(argReturnType);
  instructionModel.setIsSynchrone(argIsSyncrhone);

  return instructionModel;
};

InstructionFactoryUtils:AInstructionModel	create(QByteArray *byteArray)
{
  AInstructionModel				instructionModel(byteArray);

  return instructionModel;
};

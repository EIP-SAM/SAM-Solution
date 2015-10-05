#include "InstructionFactory.hpp"

//
// Create a message header with the instruction code
// return type and synchrone parameters
//

AInstructionModel	InstructionFactoryUtils::create(int argInstructionCode, int argReturnType, bool argIsSynchrone)
{
  AInstructionModel	instructionModel;

  instructionModel.setInstructionCode(argInstrucitonCode);
  instructionModel.setReturnType(argReturnType);
  instructionModel.setIsSynchrone(argIsSyncrhone);

  return instructionModel;
};

//
// Return a message instruction (AInstructionModel)
// based on a QByteArray to fill its attributes values 
//
AInstructionModel	InstructionFactoryUtils::create(QByteArray *byteArray)
{
  AInstructionModel	instructionModel(byteArray);

  return instructionModel;
};

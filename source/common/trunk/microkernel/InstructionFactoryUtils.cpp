#include		"InstructionFactory.hpp"

//
// Create a message header with the instruction code
// return type and synchrone parameters
//

AInstructionModel	InstructionFactoryUtils::create(int instructionCode, int returnType, bool isSynchrone)
{
  AInstructionModel	instructionModel;

  instructionModel.setInstructionCode(instrucitonCode);
  instructionModel.setReturnType(returnType);
  instructionModel.setIsSynchrone(isSyncrhone);

  return instructionModel;
};

//
// Return a message instruction (AInstructionModel)
// based on a QByteArray to fill it's attributes values 
//
AInstructionModel	InstructionFactoryUtils::create(QByteArray *byteArray)
{
  AInstructionModel	instructionModel(byteArray);

  return instructionModel;
};

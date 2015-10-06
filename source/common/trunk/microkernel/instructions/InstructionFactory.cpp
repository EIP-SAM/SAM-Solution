#include "InstructionFactory.hpp"

//
// Create a message header with the instruction code
// return type and synchrone parameters
//

InstructionFactory::InstructionFactory()
{
};

InstructionFactory::~InstructionFactory()
{
};

AInstructionModel InstructionFactory::create(int instructionCode, int returnType, bool isSynchrone)
{
  AInstructionModel instructionModel;

  instructionModel.setInstructionCode(instructionCode);
  instructionModel.setReturnType(returnType);
  instructionModel.setIsSynchrone(isSynchrone);

  return instructionModel;
};

//
// Return a message instruction (AInstructionModel)
// based on a QByteArray to fill its attributes values 
//
AInstructionModel InstructionFactory::create(QByteArray *byteArray)
{
  AInstructionModel instructionModel(byteArray);

  return instructionModel;
};

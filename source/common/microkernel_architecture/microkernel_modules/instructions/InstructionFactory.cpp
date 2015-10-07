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

ANetworkInstruction InstructionFactory::create(int instructionCode, int returnType, bool isSynchrone)
{
  ANetworkInstruction instructionModel;

  instructionModel.setInstructionCode(instructionCode);
  instructionModel.setReturnType(returnType);
  instructionModel.setIsSynchrone(isSynchrone);

  return instructionModel;
};

//
// Return a message instruction (AInstructionModel)
// based on a QByteArray to fill its attributes values
//
ANetworkInstruction InstructionFactory::create(QByteArray *byteArray)
{
  ANetworkInstruction instructionModel(byteArray);

  return instructionModel;
};

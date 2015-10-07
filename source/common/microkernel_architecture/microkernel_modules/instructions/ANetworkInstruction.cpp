#include "ANetworkInstruction.hpp"

ANetworkInstruction::ANetworkInstruction()
{
  _init();
}

//
// This constructor create a copy of a QByteArray: pointer and value
//

ANetworkInstruction::ANetworkInstruction(QByteArray *byteArray)
{
  int *intPtr;
  bool *boolPtr;
  const char *content;

  _init();

  content = byteArray->constData();
  intPtr = (int*)&(content[INDEX_BYTE_INSTRUCTIONCODE]);
  setInstructionCode(*intPtr);
  intPtr = (int*)&(content[INDEX_BYTE_RETURNTYPE]);
  setReturnType(*intPtr);
  boolPtr = (bool*)&(content[INDEX_BYTE_ISSYNCHRONE]);
  setIsSynchrone(*boolPtr);
}

ANetworkInstruction::~ANetworkInstruction()
{
}

//
// Stock in the attribut _byteArray pointer to other attributs to define number of bytes
// Add default value to attributs
//

void ANetworkInstruction::_init()
{
  char *ptr = NULL;

  _byteArray = new QByteArray(CONTENT_BYTE_SIZE, '\0');

  ptr = _byteArray->data();
  _instructionCode = (int*)&(ptr[INDEX_BYTE_INSTRUCTIONCODE]);
  _returnType = (int*)&(ptr[INDEX_BYTE_RETURNTYPE]);
  _isSynchrone = (bool*)&(ptr[INDEX_BYTE_ISSYNCHRONE]);

  setInstructionCode(0);
  setReturnType(0);
  setIsSynchrone(false);
}

void ANetworkInstruction::setInstructionCode(int instructionCode)
{
  *_instructionCode = instructionCode;
}

int ANetworkInstruction::getInstructionCode() const
{
  return *_instructionCode;
}

void ANetworkInstruction::setReturnType(int returnType)
{
  *_returnType = returnType;
}

int ANetworkInstruction::getReturnType() const
{
  return *_returnType;
}

void ANetworkInstruction::setIsSynchrone(bool isSynchrone)
{
  *_isSynchrone = isSynchrone;
}

bool ANetworkInstruction::getIsSynchrone() const
{
  return *_isSynchrone;
}

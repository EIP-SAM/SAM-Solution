#include				"AInstruction.hpp"
#include <iostream>

AInstruction::AInstruction(QByteArray byteArray)
{
  _byteArray = byteArray;
}

AInstruction::AInstruction()
{
  _byteArray = new QByteArray();

  QByteArray *instructionCode = new QByteArray(4, '\0');
  _instructionCode = (int *)instructionCode->constData();
  _byteArray->append(*instructionCode);

  QByteArray *returnType = new QByteArray(4, '\0');
  _returnType = (int *)returnType->constData();
  _byteArray->append(*returnType);

  QByteArray *isSynchrone = new QByteArray(1, '\0');
  _isSynchrone = (bool *)isSynchrone->constData();
  _byteArray->append(*isSynchrone);  

  // setInstructionCode(7);
  // std::cerr << getInstructionCode() << std::endl;
  // std::cerr << *((int *)_byteArray->constData()) << std::endl;
}

AInstruction::~AInstruction()
{
}

void					AInstruction::setInstructionCode(int instructionCode)
{
  *_instructionCode = instructionCode;
}

int					AInstruction::getInstructionCode() const
{
  return (*_instructionCode);
}

void					AInstruction::setReturnType(int returnType)
{
  *_returnType = returnType;
}

int					AInstruction::getReturnType() const
{
  return (*_returnType);
}

void					AInstruction::setIsSynchrone(bool isSynchrone)
{
  *_isSynchrone = isSynchrone;
}

bool					AInstruction::getIsSynchrone() const
{
  return (*_isSynchrone);
}

void					AInstruction::setByteArray(QByteArray byteArray)
{
  *_byteArray = byteArray;
}

QByteArray				AInstruction::getByteArray() const
{
  return (*_byteArray);
}

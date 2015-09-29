#include				<iostream>
#include				<QString>
#include				<QChar>
#include				"AInstructionModel.hpp"

AInstructionModel::AInstructionModel()
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

  // TODO
  // rm it just a test
  setInstructionCode(7);
  setReturnType(2);
  setIsSynchrone(true);
  AInstructionModel *ins = new AInstructionModel(_byteArray);
  (void) ins;
}

AInstructionModel::AInstructionModel(QByteArray *byteArray)
{
  int					nbBytes[3] = {4, 4, 1};
  QString				currentValue;
  int					bytePos = 0;
  QChar					currentByte;

  for (int i = 0; i < 3; i++)
    {
      std::cout << "aaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
      for (int j = 0; j < nbBytes[i]; j++)
	{
	  std::cout << "bbbbbbbbbbbbbbbbbbbbbb" << std::endl;
	  std::cout << bytePos << std::endl;
	  currentByte = byteArray->at(bytePos);
	  currentValue.append(currentByte);
	  bytePos++;
	}
      std::cout << "ccccccccccccccccccccccccc" << std::endl;
      if (i == 0)
	setInstructionCode(currentValue.toInt());
      else if (i == 1)
	setReturnType(currentValue.toInt());
      else
	setIsSynchrone((bool) currentByte.row());
      std::cout << "dddddddddddddddddddddddddddddd" << std::endl;
    }
  // _byteArray = byteArray;
  std::cout << getInstructionCode() << std::endl;
  std::cout << getReturnType() << std::endl;
  std::cout << getIsSynchrone() << std::endl;
}

AInstructionModel::~AInstructionModel()
{
}

void					AInstructionModel::setInstructionCode(int instructionCode)
{
  *_instructionCode = instructionCode;
}

int					AInstructionModel::getInstructionCode() const
{
  return (*_instructionCode);
}

void					AInstructionModel::setReturnType(int returnType)
{
  *_returnType = returnType;
}

int					AInstructionModel::getReturnType() const
{
  return (*_returnType);
}

void					AInstructionModel::setIsSynchrone(bool isSynchrone)
{
  *_isSynchrone = isSynchrone;
}

bool					AInstructionModel::getIsSynchrone() const
{
  return (*_isSynchrone);
}

void					AInstructionModel::setByteArray(QByteArray *byteArray)
{
  _byteArray = byteArray;
}

QByteArray				*AInstructionModel::getByteArray() const
{
  return (_byteArray);
}

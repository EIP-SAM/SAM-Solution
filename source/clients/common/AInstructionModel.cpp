#include				"AInstructionModel.hpp"

AInstructionModel::AInstructionModel()
{
  _init();
}

AInstructionModel::AInstructionModel(QByteArray *byteArray)
{
  int					*intPtr;
  bool					*boolPtr;
  const char				*content;

  _init();

  content = byteArray->constData();
  intPtr = (int*)&(content[INDEX_BYTE_INSTRUCTIONCODE]);
  setInstructionCode(*intPtr);
  intPtr = (int*)&(content[INDEX_BYTE_RETURNTYPE]);
  setReturnType(*intPtr);
  boolPtr = (bool*)&(content[INDEX_BYTE_ISSYNCHRONE]);
  setIsSynchrone(*boolPtr);
}

AInstructionModel::~AInstructionModel()
{
}

void					AInstructionModel::_refreshByteArray() {
  _byteArray->clear();
  for (int i = 0; i < CONTENT_BYTE_SIZE; ++i) {
    _byteArray->append(_content[i]);
  }
}

void					AInstructionModel::_init() {
  _byteArray = new QByteArray();

  _instructionCode = (int*)&(_content[INDEX_BYTE_INSTRUCTIONCODE]);
  _returnType = (int*)&(_content[INDEX_BYTE_RETURNTYPE]);
  _isSynchrone = (bool*)&(_content[INDEX_BYTE_ISSYNCHRONE]);
  _content[CONTENT_BYTE_SIZE - 1] = '\0';

  _refreshByteArray();

}

void					AInstructionModel::setInstructionCode(int instructionCode)
{
  *_instructionCode = instructionCode;
  _refreshByteArray();
}

int					AInstructionModel::getInstructionCode() const
{
  return (*_instructionCode);
}

void					AInstructionModel::setReturnType(int returnType)
{
  *_returnType = returnType;
  _refreshByteArray();
}

int					AInstructionModel::getReturnType() const
{
  return (*_returnType);
}

void					AInstructionModel::setIsSynchrone(bool isSynchrone)
{
  *_isSynchrone = isSynchrone;
  _refreshByteArray();
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

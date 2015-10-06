#include		"TestAInstructionModel.hpp"

TestAInstructionModel::TestAInstructionModel()
{
}

TestAInstructionModel::~TestAInstructionModel()
{
}

//
// Test function init if attributs have correct default value
//

void			TestAInstructionModel::_init()
{
  AInstructionModel	*instructionModel = new AInstructionModel();

  QCOMPARE(instructionModel->getByteArray()->size(), CONTENT_BYTE_SIZE);
  QCOMPARE(instructionModel->getInstructionCode(), 0);
  QCOMPARE(instructionModel->getReturnType(), 0);
  QCOMPARE(instructionModel->getIsSynchrone(), false);
}

//
// Test pointer and second constructor
//

void			TestAInstructionModel::ptrTest()
{
  AInstructionModel     *instructionModel = new AInstructionModel();
  char			*ptr = NULL;

  instructionModel->setInstructionCode(27);
  instructionModel->setReturnType(9);
  instructionModel->setIsSynchrone(true);
  QCOMPARE(instructionModel->getInstructionCode(), 27);
  QCOMPARE(instructionModel->getReturnType(), 9);
  QCOMPARE(instructionModel->getIsSynchrone(), true);

  ptr = instructionModel->getByteArray()->data();
  QCOMPARE(*((int*)&(ptr[INDEX_BYTE_INSTRUCTIONCODE])), 27);
  QCOMPARE(*((int*)&(ptr[INDEX_BYTE_RETURNTYPE])), 9);
  QCOMPARE(*((bool*)&(ptr[INDEX_BYTE_ISSYNCHRONE])), true);

  AInstructionModel	*instructionModel2 = new AInstructionModel(instructionModel->getByteArray());

  QCOMPARE(instructionModel2->getInstructionCode(), 27);
  QCOMPARE(instructionModel2->getReturnType(), 9);
  QCOMPARE(instructionModel2->getIsSynchrone(), true);
  ptr = instructionModel2->getByteArray()->data();
  QCOMPARE(*((int*)&(ptr[INDEX_BYTE_INSTRUCTIONCODE])), 27);
  QCOMPARE(*((int*)&(ptr[INDEX_BYTE_RETURNTYPE])), 9);
  QCOMPARE(*((bool*)&(ptr[INDEX_BYTE_ISSYNCHRONE])), true);
}

//
// QTEST_MAIN(TestAInstructionModel)
//

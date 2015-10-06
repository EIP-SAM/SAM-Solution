#include		"TestInstructionFactoryUtils.hpp"

TestInstructionFactoryUtils::TestInstructionFactoryUtils()
{
}

TestInstructionFactoryUtils::~TestInstructionFactoryUtils()
{
}

//
// Test if the method create (with three parameters) return a
// AInstructionModel with correct attribute values
//

void			TestInstructionFactoryUtils::TestCreate()
{
  AInstructionModel	message = InstructionFactoryUtils::create(1, 15, false);
  QCOMPARE(message.getInstructionCode(), 1);
  QCOMPARE(message.getReturnType(), 15);
  QCOMPARE(message.getIsSynchrone(), false);
}

//
// Test if the method create (with a QByteArray) return a
// AInstructionModel with correct attribute values
//

void			TestInstructionFactoryUtils::TestCreateArray()
{
  AInstructionModel	message = InstructionFactoryUtils::create(1, 15, false);
  QByteArray		*messageArray = NULL;

  messageArray = message.getByteArray();

  AInstructionModel	messageTest = InstructionFactoryUtils::create(messageArray);

  QCOMPARE(messageTest.getInstructionCode(), 1);
  QCOMPARE(messageTest.getReturnType(), 15);
  QCOMPARE(messageTest.getIsSynchrone(), false);
}

QTEST_MAIN(TestInstructionFactoryUtils)

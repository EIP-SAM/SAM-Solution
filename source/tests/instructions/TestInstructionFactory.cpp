#include "TestInstructionFactory.hpp"

TestInstructionFactory::TestInstructionFactory()
{
}

TestInstructionFactory::~TestInstructionFactory()
{
}

//
// Test if the method create (with three parameters) return a
// AInstructionModel with correct attribute values
//

void TestInstructionFactory::_TestCreate()
{
  ANetworkInstruction message = InstructionFactory::create(1, 15, false);
  QCOMPARE(message.getInstructionCode(), 1);
  QCOMPARE(message.getReturnType(), 15);
  QCOMPARE(message.getIsSynchrone(), false);
}

//
// Test if the method create (with a QByteArray) return a
// AInstructionModel with correct attribute values
//

void TestInstructionFactory::_TestCreateArray()
{
  ANetworkInstruction message = InstructionFactory::create(1, 15, false);
  QByteArray *messageArray = NULL;

  messageArray = message.getByteArray();

  ANetworkInstruction messageTest = InstructionFactory::create(messageArray);

  QCOMPARE(messageTest.getInstructionCode(), 1);
  QCOMPARE(messageTest.getReturnType(), 15);
  QCOMPARE(messageTest.getIsSynchrone(), false);
}

QTEST_MAIN(TestInstructionFactory)

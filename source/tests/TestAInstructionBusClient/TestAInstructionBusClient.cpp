#include "AInstructionBusClient.hpp"
#include "AInstruction.hpp"
#include <QString>
#include <QtTest>

//
// Note: `TestAInstructionBusClient` inherits from `AInstructionBusClient`
//  to be able to access protected and private members
//

class TestAInstructionBusClient : public AInstructionBusClient
{
    Q_OBJECT

public:
    TestAInstructionBusClient();

private Q_SLOTS:
    void testClientId();
    void testInstructionPushedSlotEnabled();
    void testInstructionQueue();
};

//
// Constructor
//
TestAInstructionBusClient::TestAInstructionBusClient()
    : AInstructionBusClient(INVALID)
{
}

//
// Test instruction bus client id
//
void TestAInstructionBusClient::testClientId()
{
    AInstructionBusClient client(AInstructionBusClient::INVALID);

    QVERIFY(client.getClientId() == AInstructionBusClient::INVALID);
}

//
// Test instruction pushed slot attribute
//
void TestAInstructionBusClient::testInstructionPushedSlotEnabled()
{
    AInstructionBusClient client(AInstructionBusClient::INVALID);

    QVERIFY(client.instructionPushedSlotEnabled() == false);

    client.enableInstructionPushedSlot();
    QVERIFY(client.instructionPushedSlotEnabled() == true);
}

//
// Test instruction queue
// Note: `TestAInstructionBusClient` is used instead of `AInstructionBusClient`
// to be able to access `_popInstruction()` from the unit test
//
void TestAInstructionBusClient::testInstructionQueue()
{
    TestAInstructionBusClient client;
    AInstruction *instructionInput = new AInstruction(), *instructionOutput = NULL;

    QVERIFY(client._popInstruction() == NULL);
    client.pushInstruction(instructionInput);
    instructionOutput = client._popInstruction();
    QVERIFY(instructionInput == instructionOutput);
}

QTEST_APPLESS_MAIN(TestAInstructionBusClient)

#include "TestAInstructionBusClient.moc"

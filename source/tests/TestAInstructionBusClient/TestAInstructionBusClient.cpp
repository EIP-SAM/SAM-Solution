#include "AInstructionBusClient.hpp"
#include "AInstruction.hpp"
#include <QString>
#include <QtTest>

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

TestAInstructionBusClient::TestAInstructionBusClient()
    : AInstructionBusClient(INVALID)
{
}

void TestAInstructionBusClient::testClientId()
{
    AInstructionBusClient client(AInstructionBusClient::INVALID);

    QVERIFY(client.getClientId() == AInstructionBusClient::INVALID);
}

void TestAInstructionBusClient::testInstructionPushedSlotEnabled()
{
    AInstructionBusClient client(AInstructionBusClient::INVALID);

    QVERIFY(client.instructionPushedSlotEnabled() == false);

    client.enableInstructionPushedSlot();
    QVERIFY(client.instructionPushedSlotEnabled() == true);
}

// `TestAInstructionBusClient` is used instead of `AInstructionBusClient`
// to be able to access `_popInstruction()` from the unit test
void TestAInstructionBusClient::testInstructionQueue()
{
    TestAInstructionBusClient client;
    AInstruction *instructionInput = new AInstruction(), *instructionOutput = NULL;

    client.pushInstruction(instructionInput);
    instructionOutput = client._popInstruction();
    QVERIFY(instructionInput == instructionOutput);
}

QTEST_APPLESS_MAIN(TestAInstructionBusClient)

#include "TestAInstructionBusClient.moc"

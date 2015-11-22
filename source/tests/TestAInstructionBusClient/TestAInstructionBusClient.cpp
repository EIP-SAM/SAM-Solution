#include <QString>
#include <QtTest>

class TestAInstructionBusClient : public QObject
{
    Q_OBJECT

public:
    TestAInstructionBusClient();

private Q_SLOTS:
    void testCase1();
};

TestAInstructionBusClient::TestAInstructionBusClient()
{
}

void TestAInstructionBusClient::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestAInstructionBusClient)

#include "TestAInstructionBusClient.moc"

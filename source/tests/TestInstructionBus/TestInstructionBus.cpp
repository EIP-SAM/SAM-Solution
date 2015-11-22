#include <QString>
#include <QtTest>

class TestInstructionBus : public QObject
{
    Q_OBJECT

public:
    TestInstructionBus();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

TestInstructionBus::TestInstructionBus()
{
}

void TestInstructionBus::initTestCase()
{
}

void TestInstructionBus::cleanupTestCase()
{
}

void TestInstructionBus::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestInstructionBus)

#include "TestInstructionBus.moc"

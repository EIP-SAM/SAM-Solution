#include <QString>
#include <QtTest>

class TestInstructionBuffer : public QObject
{
    Q_OBJECT

public:
    TestInstructionBuffer();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

TestInstructionBuffer::TestInstructionBuffer()
{
}

void TestInstructionBuffer::initTestCase()
{
}

void TestInstructionBuffer::cleanupTestCase()
{
}

void TestInstructionBuffer::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestInstructionBuffer)

#include "TestInstructionBuffer.moc"

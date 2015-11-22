#include <QString>
#include <QtTest>
#include "InstructionBuffer.hpp"

//
// Note: Test class inherit from `InstructionBuffer` to be able to
//  access private and protected structures definitions and static
//  internal data
//

class TestInstructionBuffer : public QObject, InstructionBuffer
{
    Q_OBJECT

public:
    TestInstructionBuffer();

private Q_SLOTS:
    void testFillingValidInstructionWithoutParameter();
    void testFillingValidInstructionWithOneParameter();
    void testFillingTooMuchDataAppend();
    void testFillingNotEnoughDataAppend();
    void testFillingParameterHeaderTruncated();
    void testFillingInstructionHeaderTruncated();
    void testEmptyInstruction();
};

TestInstructionBuffer::TestInstructionBuffer()
{
}

void TestInstructionBuffer::testFillingValidInstructionWithoutParameter()
{
    InstructionBuffer instruction;
    instructionHeader_t instructionHeader = {0x10101042, eProgId::INVALID, (AInstructionBusClient::eClientId)0, (AInstructionBusClient::eClientId)0, 0, 0, 0};

    instruction = QByteArray((char *)&instructionHeader, sizeof(instructionHeader_t));
    QVERIFY(instruction.finalizeFilling() == true);
    QVERIFY(instruction.getParameterNumber(1) == NULL);
}

void TestInstructionBuffer::testFillingValidInstructionWithOneParameter()
{
    InstructionBuffer instruction;
    instructionHeader_t instructionHeader = {0x10101042, eProgId::INVALID, (AInstructionBusClient::eClientId)0, (AInstructionBusClient::eClientId)0, 0, 0, 1};
    instructionParameterHeader_t instructionParamHeader = {21, 0};
    Parameter *parameter = NULL;

    instruction = QByteArray((char *)&instructionHeader, sizeof(instructionHeader_t));
    instruction << QByteArray((char *)&instructionParamHeader, sizeof(instructionParameterHeader_t));
    QVERIFY(instruction.finalizeFilling() == true);
    QVERIFY(parameter = instruction.getParameterNumber(1));
    QVERIFY(instruction.getParameterNumber(2) == NULL);
    QVERIFY(parameter->getSize() == 0);
    QVERIFY(parameter->getType() == 21);
}

void TestInstructionBuffer::testFillingTooMuchDataAppend()
{
    InstructionBuffer instruction;
    instructionHeader_t instructionHeader = {0x10101042, eProgId::INVALID, (AInstructionBusClient::eClientId)0, (AInstructionBusClient::eClientId)0, 0, 0, 1};
    instructionParameterHeader_t instructionParamHeader = {21, 0};

    instruction = QByteArray((char *)&instructionHeader, sizeof(instructionHeader_t));
    instruction << QByteArray((char *)&instructionParamHeader, sizeof(instructionParameterHeader_t));
    instruction << QByteArray(300, 0);
    QVERIFY(instruction.finalizeFilling() == false);
    QVERIFY(instruction.getParameterNumber(1) == NULL);
}

void TestInstructionBuffer::testFillingNotEnoughDataAppend()
{
    InstructionBuffer instruction;
    instructionHeader_t instructionHeader = {0x10101042, eProgId::INVALID, (AInstructionBusClient::eClientId)0, (AInstructionBusClient::eClientId)0, 0, 0, 400};
    instructionParameterHeader_t instructionParamHeader = {21, 0};

    instruction = QByteArray((char *)&instructionHeader, sizeof(instructionHeader_t));
    instruction << QByteArray((char *)&instructionParamHeader, sizeof(instructionParameterHeader_t));
    instruction << QByteArray(1, 0);
    QVERIFY(instruction.finalizeFilling() == false);
    QVERIFY(instruction.getParameterNumber(1) == NULL);
}

void TestInstructionBuffer::testFillingParameterHeaderTruncated()
{
    InstructionBuffer instruction;
    instructionHeader_t instructionHeader = {0x10101042, eProgId::INVALID, (AInstructionBusClient::eClientId)0, (AInstructionBusClient::eClientId)0, 0, 0, 1};
    instructionParameterHeader_t instructionParamHeader = {21, 0};

    instruction = QByteArray((char *)&instructionHeader, sizeof(instructionHeader_t));
    instruction << QByteArray((char *)&instructionParamHeader, sizeof(instructionParameterHeader_t) - 1);
    QVERIFY(instruction.finalizeFilling() == false);
    QVERIFY(instruction.getParameterNumber(1) == NULL);
}

void TestInstructionBuffer::testFillingInstructionHeaderTruncated()
{
    InstructionBuffer instruction;
    instructionHeader_t instructionHeader = {0x10101042, eProgId::INVALID, (AInstructionBusClient::eClientId)0, (AInstructionBusClient::eClientId)0, 0, 0, 1};

    instruction = QByteArray((char *)&instructionHeader, sizeof(instructionHeader_t) - 1);
    QVERIFY(instruction.finalizeFilling() == false);
    QVERIFY(instruction.getParameterNumber(1) == NULL);
}

void TestInstructionBuffer::testEmptyInstruction()
{
    InstructionBuffer instruction;

    QVERIFY(instruction.finalizeFilling() == false);
    QVERIFY(instruction.getParameterNumber(1) == NULL);
}

QTEST_APPLESS_MAIN(TestInstructionBuffer)

#include "TestInstructionBuffer.moc"

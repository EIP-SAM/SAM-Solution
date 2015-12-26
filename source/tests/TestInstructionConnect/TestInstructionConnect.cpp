#include "TestInstructionConnect.hpp"
#include "AInstruction.hpp"
#include "ReturnType.hpp"
#include "AInstructionBusClient.hpp"
#include <QtTest/QtTest>
#include <iostream>

TestInstructionConnect::TestInstructionConnect()
{
}

TestInstructionConnect::~TestInstructionConnect()
{
}

void TestInstructionConnect::TestConstructObject()
{
    Connect *co = new Connect("Login", "Password", SAM_SERVER, AInstructionBusClient::eClientId::INVALID, AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(co->getTransmitterProgId(), SAM_SERVER);
    QCOMPARE(co->getFirstTransmitter(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(co->getFinalReceiver(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(co->getInstructionCode(), (unsigned int)1);
    QCOMPARE(co->getReturnType(), (unsigned int)ReturnType::BOOLEAN);
    QCOMPARE(co->getNumberOfParameters(), 2);
    AInstruction::Parameter *param1 = co->getParameterNumber(1);
    QCOMPARE(param1->getType(), (unsigned int)ReturnType::QSTRING);
    QCOMPARE(param1->getSize(), 5);
    QCOMPARE(param1->getRawData().data(), "Login");
    AInstruction::Parameter *param2 = co->getParameterNumber(2);
    QCOMPARE(param2->getType(), (unsigned int)ReturnType::QSTRING);
    QCOMPARE(param2->getSize(), 8);
    QCOMPARE(param2->getRawData().data(), "Password");

    Connect *co2 = new Connect(co);
    QCOMPARE(co2->getTransmitterProgId(), SAM_SERVER);
    QCOMPARE(co2->getFirstTransmitter(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(co2->getFinalReceiver(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(co2->getInstructionCode(), (unsigned int)1);
    QCOMPARE(co2->getReturnType(), (unsigned int)ReturnType::BOOLEAN);
    QCOMPARE(co2->getNumberOfParameters(), 2);
    AInstruction::Parameter *param21 = co2->getParameterNumber(1);
    QCOMPARE(param21->getType(), (unsigned int)ReturnType::QSTRING);
    QCOMPARE(param21->getSize(), 5);
    QCOMPARE(param21->getRawData().data(), "Login");
    AInstruction::Parameter *param22 = co2->getParameterNumber(2);
    QCOMPARE(param22->getType(), (unsigned int)ReturnType::QSTRING);
    QCOMPARE(param22->getSize(), 8);
    QCOMPARE(param22->getRawData().data(), "Password");
}

QTEST_MAIN(TestInstructionConnect)

#include "TestInstructionDisconnect.hpp"
#include "AInstructionBusClient.hpp"
#include "ReturnType.hpp"

TestInstructionDisconnect::TestInstructionDisconnect()
{
}

TestInstructionDisconnect::~TestInstructionDisconnect()
{
}

void TestInstructionDisconnect::TestConstructObject()
{
    Disconnect *disconnect = new Disconnect(SAM_SERVER, AInstructionBusClient::eClientId::INVALID, AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(disconnect->getTransmitterProgId(), SAM_SERVER);
    QCOMPARE(disconnect->getFirstTransmitter(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(disconnect->getFinalReceiver(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(disconnect->getInstructionCode(), (unsigned int)2);
    QCOMPARE(disconnect->getReturnType(), (unsigned int)ReturnType::BOOLEAN);
    QCOMPARE(disconnect->getNumberOfParameters(), 0);

    Disconnect *disconnect2 = new Disconnect(disconnect);
    QCOMPARE(disconnect2->getTransmitterProgId(), SAM_SERVER);
    QCOMPARE(disconnect2->getFirstTransmitter(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(disconnect2->getFinalReceiver(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(disconnect2->getInstructionCode(), (unsigned int)2);
    QCOMPARE(disconnect2->getReturnType(), (unsigned int)ReturnType::BOOLEAN);
    QCOMPARE(disconnect2->getNumberOfParameters(), 0);
}

QTEST_MAIN(TestInstructionDisconnect)

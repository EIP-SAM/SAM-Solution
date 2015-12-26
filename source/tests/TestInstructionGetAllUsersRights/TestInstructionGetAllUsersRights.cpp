#include "TestInstructionGetAllUsersRights.hpp"
#include "AInstructionBusClient.hpp"
#include "ReturnType.hpp"

TestInstructionGetAllUsersRights::TestInstructionGetAllUsersRights()
{
}

TestInstructionGetAllUsersRights::~TestInstructionGetAllUsersRights()
{
}

void TestInstructionGetAllUsersRights::TestConstructObject()
{
    GetAllUsersRights *getAllUsersRights = new GetAllUsersRights(SAM_SERVER, AInstructionBusClient::eClientId::INVALID, AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(getAllUsersRights->getTransmitterProgId(), SAM_SERVER);
    QCOMPARE(getAllUsersRights->getFirstTransmitter(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(getAllUsersRights->getFinalReceiver(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(getAllUsersRights->getInstructionCode(), (unsigned int)6);
    QCOMPARE(getAllUsersRights->getReturnType(), (unsigned int)ReturnType::QLIST_USERS);
    QCOMPARE(getAllUsersRights->getNumberOfParameters(), 0);

    GetAllUsersRights *getAllUsersRights2 = new GetAllUsersRights(getAllUsersRights);
    QCOMPARE(getAllUsersRights2->getTransmitterProgId(), SAM_SERVER);
    QCOMPARE(getAllUsersRights2->getFirstTransmitter(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(getAllUsersRights2->getFinalReceiver(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(getAllUsersRights2->getInstructionCode(), (unsigned int)6);
    QCOMPARE(getAllUsersRights2->getReturnType(), (unsigned int)ReturnType::QLIST_USERS);
    QCOMPARE(getAllUsersRights2->getNumberOfParameters(), 0);
}

QTEST_MAIN(TestInstructionGetAllUsersRights)

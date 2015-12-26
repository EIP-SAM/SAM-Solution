#include "TestInstructionCreateUser.hpp"
#include "ReturnType.hpp"
#include "AInstructionBusClient.hpp"
#include <iostream>

TestInstructionCreateUser::TestInstructionCreateUser()
{
}

TestInstructionCreateUser::~TestInstructionCreateUser()
{
}

void TestInstructionCreateUser::TestConstructObject()
{
    CreateUser *createUser = new CreateUser("Login", 1011, SAM_SERVER,
					    AInstructionBusClient::eClientId::INVALID,
					    AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(createUser->getTransmitterProgId(), SAM_SERVER);
    QCOMPARE(createUser->getFirstTransmitter(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(createUser->getFinalReceiver(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(createUser->getInstructionCode(), (unsigned int)7);
    QCOMPARE(createUser->getReturnType(), (unsigned int)ReturnType::QSTRING);
    QCOMPARE(createUser->getNumberOfParameters(), 2);
    AInstruction::Parameter *param1 = createUser->getParameterNumber(1);
    QCOMPARE(param1->getType(), (unsigned int)ReturnType::QSTRING);
    QCOMPARE(param1->getSize(), 5);
    QCOMPARE(param1->getRawData().data(), "Login");
    AInstruction::Parameter *param2 = createUser->getParameterNumber(2);
    QCOMPARE(param2->getType(), (unsigned int)ReturnType::INTEGER);
    QCOMPARE(param2->getSize(), 4);
    QCOMPARE(param2->getRawData().data(), std::to_string(1011).c_str());

    CreateUser *createUser2 = new CreateUser(createUser);
    QCOMPARE(createUser2->getTransmitterProgId(), SAM_SERVER);
    QCOMPARE(createUser2->getFirstTransmitter(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(createUser2->getFinalReceiver(), AInstructionBusClient::eClientId::INVALID);
    QCOMPARE(createUser2->getInstructionCode(), (unsigned int)7);
    QCOMPARE(createUser2->getReturnType(), (unsigned int)ReturnType::QSTRING);
    QCOMPARE(createUser2->getNumberOfParameters(), 2);
    AInstruction::Parameter *param21 = createUser2->getParameterNumber(1);
    QCOMPARE(param21->getType(), (unsigned int)ReturnType::QSTRING);
    QCOMPARE(param21->getSize(), 5);
    QCOMPARE(param21->getRawData().data(), "Login");
    AInstruction::Parameter *param22 = createUser2->getParameterNumber(2);
    QCOMPARE(param22->getType(), (unsigned int)ReturnType::INTEGER);
    QCOMPARE(param22->getSize(), 4);
    QCOMPARE(param22->getRawData().data(), std::to_string(1011).c_str());
}

QTEST_MAIN(TestInstructionCreateUser)

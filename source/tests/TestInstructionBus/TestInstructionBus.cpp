#include "InstructionBus.hpp"
#include "AInstruction.hpp"
#include "FooBusClient.hpp"
#include "BarBusClient.hpp"
#include <QString>
#include <QtTest>

class TestInstructionBus : public QObject
{
    Q_OBJECT

private:
    InstructionBus *_bus = NULL;
    FooBusClient *_foo = NULL;
    BarBusClient *_bar = NULL;

public:
    TestInstructionBus();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testRegisterClients();
    void testSendInstructionInFoo();
    void testReceiveInstructionInBar();
};

//
// Constructor
//
TestInstructionBus::TestInstructionBus()
{
}

//
// Initialization test case
//
void TestInstructionBus::initTestCase()
{
    _bus = new InstructionBus;
    _foo = new FooBusClient((AInstructionBusClient::eClientId)10);
    _bar = new BarBusClient((AInstructionBusClient::eClientId)11);
    QVERIFY(_bus->init() == true);
}

//
// Cleanup test case
//
void TestInstructionBus::cleanupTestCase()
{
    delete _bus;
    delete _foo;
    delete _bar;
}

//
// Test clients registering
//
void TestInstructionBus::testRegisterClients()
{
    QVERIFY(_bus->registerClient((AInstructionBusClient::eClientId)10, _foo) == true);
    QVERIFY(_bus->registerClient((AInstructionBusClient::eClientId)11, _bar) == true);
}

//
// Test sending of a valid instruction from a client to another
// Note: Theoreticaly, this is not possible to use the instruction bus this way
//  since it is encapsulated in `AMainController`
//
void TestInstructionBus::testSendInstructionInFoo()
{
    AInstruction *input = NULL;

    input = new AInstruction;
    input->setLocalTransmitter(_foo);
    input->setFirstTransmitter((AInstructionBusClient::eClientId)10);
    input->setFinalReceiver((AInstructionBusClient::eClientId)11);
    input->setInstructionCode(42);
    QVERIFY(_bus->pushInstruction(input) == true);
}

//
// Test receiving of the instruction previously sent
//
void TestInstructionBus::testReceiveInstructionInBar()
{
    AInstruction *output = NULL;

    QThread::sleep(1);
    QVERIFY(output = _bar->getInstruction());
    QVERIFY(output->getInstructionCode() == 42);
    delete output;
}

QTEST_APPLESS_MAIN(TestInstructionBus)

#include "TestInstructionBus.moc"

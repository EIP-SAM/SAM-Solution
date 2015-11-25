#include "TestAFunctionalitiesManager.hpp"

//
// Constructor
//
TestAFunctionalitiesManager::TestAFunctionalitiesManager() : _mainController(NULL)
{
}

//
// Test init function
//
void TestAFunctionalitiesManager::_testInit()
{
    ac = 1;
    av = NULL;
    _mainController = new MainController(ac, av);
    _mainController->getInstructionBus().init();

    BasicFunctionalitiesManager &fctsManager = _mainController->getFctsManager();
    bool functionalitiesManagerInitValue = fctsManager.init();

    QCOMPARE(functionalitiesManagerInitValue, true);
    QCOMPARE(fctsManager.getNumberOfMicrokernelFcts(), 1);
    QCOMPARE(fctsManager.getNumberOfInternalFcts(), 2);
    QCOMPARE(fctsManager.getNumberOfExternalFcts(), 3);
    QTest::qWait(500);
    QCOMPARE(fctsManager.getNumberOfRunningFcts(), 6);

    delete _mainController;
}

//
// Test shutDown function
//
void TestAFunctionalitiesManager::_testShutdown()
{
    _mainController = new MainController(ac, av);
    _mainController->getInstructionBus().init();

    BasicFunctionalitiesManager &fctsManager = 
        _mainController->getFctsManager();

    fctsManager.init();
    QTest::qWait(500);

    QSignalSpy readyToDeleteSpy(&fctsManager, SIGNAL(readyToDelete()));

    fctsManager.shutdown();
    QTest::qWait(500);
    QCOMPARE(readyToDeleteSpy.count(), 1);
    QCOMPARE(fctsManager.getNumberOfRunningFcts(), 0);

    delete _mainController;
}

//
// Test loadLibrary function
//
void TestAFunctionalitiesManager::_testLoadLibrary()
{
    
}

//
// Test getFunctionalityType
//

void TestAFunctionalitiesManager::_testGetFunctionalityType()
{
    _mainController = new MainController(ac, av);
    _mainController->getInstructionBus().init();

    BasicFunctionalitiesManager &fctsManager = 
        _mainController->getFctsManager();
    
    fctsManager.init();
    QTest::qWait(500);
    
    AFunctionality::eType result = AFunctionality::INVALID;

    result = fctsManager.getFunctionalityType(AFunctionality::eClientId::NETWORK_MANAGER);
    QCOMPARE(result, AFunctionality::MICROKERNEL);
    
    result = fctsManager.getFunctionalityType(AFunctionality::eClientId::INVALID);
    QCOMPARE(result, AFunctionality::INVALID);
    
    result = fctsManager.getFunctionalityType(AFunctionality::eClientId::ALL);
    QCOMPARE(result, AFunctionality::INVALID);

    delete _mainController;
}

QTEST_MAIN(TestAFunctionalitiesManager);

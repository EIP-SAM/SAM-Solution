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
    _mainController = new MainController(1, NULL);
    _mainController->getInstructionBus->init();

    BasicFunctionalitiesManager fctsManager = _mainController->getFonctionalitiesManager();
    bool functionalitiesManagerInitValue = fctsManager->init();

    QCOMPARE(functionalitiesManagerInitValue, true);
    QCOMPARE(fctsManager->getNumberOfMicrokernelFcts(), 1);
    QCOMPARE(fctsManager->getNumberOfInternalFcts(), 2);
    QCOMPARE(fctsManager->getNumberofExternalFcts(), 3);
    QTest::qWait(500);
    QCOMPARE(fctsManager->getNumberOfRunningFcts(), 6);

    delete _mainController;
}

//
// Test shutDown function
//
void TestAfunctionalitiesManager::_testShutdown()
{
    _mainController = new MainController(1, NULL);
    _mainController->getInstructionBus->init();

    BasicFunctionalitiesManager fctsManager = 
        _basicMainController->getFonctionalitiesManager();

    fctsManager->init();
    QTest::qWait(500);

    QSignalSpy readyToDeleteSpy(&fctsManager, SIGNAL(readyToDelete()));

    fctsManager->shutdown();
    QTest::qWait(500);
    QCOMPARE(readyToDeleteSpy.count(), 1);
    QCOMPARE(fctsManager->getNumberOfRunningFcts(), 0);

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

void TestAFunctionalitiesManager::getFunctionalityType()
{
    _mainController = new MainController(1, NULL);
    _mainController->getInstructionBus->init();

    BasicFunctionalitiesManager fctsManager = 
        _basicMainController->getFonctionalitiesManager();
    
    fctsManager->init();
    QTest::qWait(500);
    
    AFunctionality::eType resultType = AFunctionality::INVALID;

    resultType = fctsManager->getFunctionalityType(AFunctionality::NETWORK_MANAGER);
    QCOMPARE(result, AFunctionality::MICROKERNEL);
    
    resultType = fctsManager->getFunctionalityType(AFunctionality::INVALID);
    QCOMPARE(result, AFunctionality::INVALID);
    
    resultType = fctsManager->getFunctionalityType(AFunctionality::ALL);
    QCOMPARE(result, AFunctionality::INVALID);

    delete _mainController;
}

QTEST_MAIN(TestAFunctionalitiesManager);

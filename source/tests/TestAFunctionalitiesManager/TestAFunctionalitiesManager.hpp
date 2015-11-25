#ifndef TEST_AFUNCTIONALITIES_MANAGER_HPP
# define TEST_AFUNCTIONALITIES_MANAGER_HPP

# include <QtTest>
# include "BasicMainController.hpp"
# include "BasicFunctionalitiesManager.hpp"

class TestAFunctionalitiesManager : QOject {
    
    QT_OBJECT
    
    private:
        BasicMainController *_basicMainController;
        
    public:
        TestAFunctionalitiesManager();
    
    private slots:
        void _testInit();
        void _testShutdown();
        void _testLoadLibrary();
        void _testGetFunctionalityType();
        
}

#endif // !TEST_AFUNCTIONALITIES_MANAGER_HPP
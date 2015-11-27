#ifndef TEST_AFUNCTIONALITIES_MANAGER_HPP
# define TEST_AFUNCTIONALITIES_MANAGER_HPP

# include <QtTest>
# include "MainController.hpp"
# include "BasicFunctionalitiesManager.hpp"

class TestAFunctionalitiesManager : public QObject
{    
    Q_OBJECT
    
private:
    MainController *_mainController;
    int ac;
    char **av;

public:
    TestAFunctionalitiesManager();
				 
private slots:
    void _testInit();
    void _testGetFunctionalityType();
    void _testLoadLibrary();
    void _testShutdown();
};

#endif // !TEST_AFUNCTIONALITIES_MANAGER_HPP

#ifndef BASIC_FUNCTIONALITIES_MANAGER_HPP_
# define BASIC_FUNCTIONALITIES_MANAGER_HPP_

# include "AFunctionalitiesManager.hpp"
# include "BasicAFunctionality.hpp"

class BasicFunctionalitiesManager : public AFunctionalitiesManager
{

public:
    BasicFunctionalitiesManager(QObject *parent = 0);
    virtual ~BasicFunctionalitiesManager();

    int getNumberOfRunningFcts() const;
    int getNumberOfMicrokernelFcts() const;
    int getNumberOfInternalFcts() const;
    int getNumberOfExternalFcts() const;

private:
    virtual void _setFcts();
    void _setMicrokernelFcts();
    void _setInternalFcts();
    void _setExternalFcts();
};

#endif // !BASIC_FUNCTIONALITIES_MANAGER_HPP_

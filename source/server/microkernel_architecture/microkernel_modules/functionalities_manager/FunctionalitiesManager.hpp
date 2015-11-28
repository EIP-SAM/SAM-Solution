#ifndef FUNCTIONALITIES_MANAGER_HPP_
# define FUNCTIONALITIES_MANAGER_HPP_

# include "AFunctionalitiesManager.hpp"

class FunctionalitiesManager : public AFunctionalitiesManager
{
public:
    FunctionalitiesManager(QObject *parent = 0);
    virtual ~FunctionalitiesManager();

private:
    virtual void _setFcts();
    void _setMicrokernelFcts();
    void _setInternalFcts();
    void _setExternalFcts();
};

#endif // !FUNCTIONALITIES_MANAGER_HPP_

#ifndef FUNCTIONALITIES_MANAGER_HPP_
# define FUNCTIONALITIES_MANAGER_HPP_

# include "AFunctionalitiesManager.hpp"

class FunctionalitiesManager : private AFunctionalitiesManager
{
public:
    FunctionalitiesManager();
    virtual ~FunctionalitiesManager();

private:
    virtual void _setFcts();
};

#endif // !FUNCTIONALITIES_MANAGER_HPP_

#ifndef HELLO_WORLD_FUNCTIONALITY_HPP_
# define HELLO_WORLD_FUNCTIONALITY_HPP_

# include "AFunctionality.hpp"

//
// This is a temporary test class to test the good working of
// AFunctionalitiy + AInstruction + InstructionBus + NetworkManagers*
//

class HelloWorldFunctionality : public AFunctionality
{
    Q_OBJECT

public:
    HelloWorldFunctionality();

protected slots:
    virtual void _run();
};

#endif // !HELLO_WORLD_FUNCTIONALITY_HPP_

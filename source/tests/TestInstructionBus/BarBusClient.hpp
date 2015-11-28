#ifndef FOO_BAR_CLIENT_HPP_
# define FOO_BAR_CLIENT_HPP_

# include "AInstructionBusClient.hpp"

class BarBusClient : public AInstructionBusClient
{
public:
    BarBusClient();
    BarBusClient(eClientId clientId = INVALID);

    AInstruction *getInstruction();
};

#endif // !FOO_BAR_CLIENT_HPP_

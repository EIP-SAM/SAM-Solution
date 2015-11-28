#ifndef FOO_BUS_CLIENT_HPP_
# define FOO_BUS_CLIENT_HPP_

# include "AInstructionBusClient.hpp"

class FooBusClient : public AInstructionBusClient
{
public:
    FooBusClient();
    FooBusClient(eClientId clientId = INVALID);
};

#endif // !FOO_BUS_CLIENT_HPP_

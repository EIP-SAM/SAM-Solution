#ifndef ANETWORK_INSTRUCTION_HPP_
# define ANETWORK_INSTRUCTION_HPP_

# include "AInstruction.hpp"

//
// Contain the specific methods to handle an
// instruction as a I/O network buffer
//

class ANetworkInstruction : public AInstruction
{
public:
    ANetworkInstruction();
    ANetworkInstruction(const ANetworkInstruction &);
    ANetworkInstruction(const QByteArray &);
    virtual ~ANetworkInstruction();
};

#endif // !ANETWORK_INSTRUCTION_HPP_

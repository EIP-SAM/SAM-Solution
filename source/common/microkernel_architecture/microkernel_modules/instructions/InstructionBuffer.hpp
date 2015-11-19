#ifndef INSTRUCTION_BUFFER_HPP_
# define INSTRUCTION_BUFFER_HPP_

# include "AInstruction.hpp"

//
// Contain the specific methods to handle an
// instruction as a I/O buffer (for network, pipe, ...)
//

class InstructionBuffer : public AInstruction
{
private:
    int _dataValidUntilPos = 0;
    quint64 _peerId = 0;

public:
    InstructionBuffer();
    InstructionBuffer(const InstructionBuffer &o);
    InstructionBuffer(const QByteArray &data);
    virtual ~InstructionBuffer();

    InstructionBuffer &operator=(const QByteArray &data);
    InstructionBuffer &operator<<(const QByteArray &data);

    void setData(const QByteArray &data);
    void appendData(const QByteArray &data);
    void setPeerId(quint64 peerId);
    bool finalizeFilling();

    int getNextReadSize() const;
    const QByteArray &getData() const;
    quint64 getPeerId() const;
};

#endif // !INSTRUCTION_BUFFER_HPP_

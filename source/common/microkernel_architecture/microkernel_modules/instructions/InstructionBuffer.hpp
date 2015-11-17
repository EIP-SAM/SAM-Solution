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
    InstructionBuffer(const InstructionBuffer &);
    InstructionBuffer(const QByteArray &);
    virtual ~InstructionBuffer();

    InstructionBuffer &operator=(const QByteArray&);
    InstructionBuffer &operator<<(const QByteArray&);

    void setData(const QByteArray &);
    void appendData(const QByteArray &);
    void setPeerId(quint64 peerId);
    bool finalizeFilling();

    int getNextReadSize() const;
    const QByteArray &getData() const;
    quint64 getPeerId() const;
};

#endif // !INSTRUCTION_BUFFER_HPP_

#ifndef INSTRUCTION_BUFFER_HPP_
# define INSTRUCTION_BUFFER_HPP_

# include "AInstruction.hpp"

//
// Contain the specific methods to handle an
// instruction as a I/O network buffer
//

class InstructionBuffer : public AInstruction
{
private:
    int _dataValidUntilPos = 0;
    quint64 _peerId = 0;
    instructionParameterHeader_t *_parametersData = NULL;

public:
    InstructionBuffer();
    InstructionBuffer(const InstructionBuffer &);
    InstructionBuffer(const QByteArray &);
    virtual ~InstructionBuffer();

    void setRawData(const QByteArray &);
    void append(const QByteArray &);
    void append(const QByteArray &, int);
    void setPeerId(quint64 peerId);
    bool inputBufferFilled();

    int getNextReadSize() const;
    const QByteArray &getRawData() const;
    quint64 getPeerId() const;

protected:
    void _setPointersToData();

private:
    void _append(const QByteArray &, int);
};

#endif // !INSTRUCTION_BUFFER_HPP_

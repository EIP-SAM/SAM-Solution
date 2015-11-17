#include "InstructionBuffer.hpp"

#include <QDebug>

//
// Default constructor
//
InstructionBuffer::InstructionBuffer()
    : AInstruction()
{
}

//
// Copy constructor
//
InstructionBuffer::InstructionBuffer(const InstructionBuffer &o)
    : AInstruction(o), _dataValidUntilPos(o._dataValidUntilPos)
{
}

//
// Construct an `InstructionBuffer` with a byte array
// Same as `InstructionBuffer()` + `setRawData()`
//
InstructionBuffer::InstructionBuffer(const QByteArray &data)
    : AInstruction(data), _dataValidUntilPos(data.size())
{
}

//
// Destructor
//
InstructionBuffer::~InstructionBuffer()
{
}

//
// Operator `=` overload with a byte array as parameter
// Exact same as `void InstructionBuffer::setData()`
//
InstructionBuffer &InstructionBuffer::operator=(const QByteArray &data)
{
    setData(data);
    return *this;
}

//
// Operator `<<` overload with a byte array as parameter
// Exact same as `void InstructionBuffer::setData()`
//
InstructionBuffer &InstructionBuffer::operator<<(const QByteArray &data)
{
    appendData(data);
    return *this;
}

//
// Replace current `_data` by the new one in parameter
//
void InstructionBuffer::setData(const QByteArray &data)
{
    _data = data;
    _dataValidUntilPos = data.size();
    _ensureMinimumDataSize();
    _setPointerToData();
}

//
// Append `data` to `_data`
//
void InstructionBuffer::appendData(const QByteArray &data)
{
    QByteArray dataBegin(_data.left(_dataValidUntilPos));

    _dataValidUntilPos += data.size();
    _data = dataBegin + data;
    _ensureMinimumDataSize();
    _setPointerToData();
}

//
// Set transmitter id
// Note: Usefull to identify clients in a server
//
void InstructionBuffer::setPeerId(quint64 peerId)
{
    _peerId = peerId;
}

//
// Finalize the construction of the instruction
// Construct the instruction parameters from `_data`
// Return false if the instruction is in any way malformed
//
bool InstructionBuffer::finalizeFilling()
{
    Parameter *parameter = NULL;
    instructionParameterHeader_t *paramHeader = NULL;
    int i = 0, paramHeaderOffset = _FIRST_PARAMETER_OFFSET;

    if (_header->numberOfParameters > 0)
    {
        while (paramHeaderOffset < _data.size() && i++ != _header->numberOfParameters)
        {
            paramHeader = (instructionParameterHeader_t *)(((char *)_header) + paramHeaderOffset);
            if (paramHeader->parameterSize < 0 ||
                !(parameter = new (std::nothrow) Parameter(*this, paramHeader)))
                return false;
            _parameters << parameter;
            paramHeaderOffset += _INSTRUCTION_PARAMETER_HEADER_SIZE + paramHeader->parameterSize;
        }
    }
    return true;
}

//
// Get the size of the data needed to fill the instruction
// Return 0 when the instruction is supposed to be entirely filled
//
int InstructionBuffer::getNextReadSize() const
{
    instructionParameterHeader_t *paramHeader = NULL;
    int i = 0, paramHeaderOffset = _FIRST_PARAMETER_OFFSET;

    // INSTRUCTION HEADER IS NOT COMPLETE
    // Returns size needed to reconstruct an instruction header
    if (_dataValidUntilPos < _INSTRUCTION_HEADER_SIZE)
        return _INSTRUCTION_HEADER_SIZE - _dataValidUntilPos;
    // INSTRUCTION HEADER IS COMPLETE
    // Returns 0 because there is nothing supposed to be placed after the instruction header
    if (_header->numberOfParameters <= 0)
        return 0;
    while (paramHeaderOffset < _data.size() && i++ != _header->numberOfParameters)
    {
        // INSTRUCTION PARAMETER HEADER IS NOT COMPLETE
        // Returns size needed to reconstruct an instruction parameter header
        if (_dataValidUntilPos < paramHeaderOffset + _INSTRUCTION_PARAMETER_HEADER_SIZE)
            return paramHeaderOffset + _INSTRUCTION_PARAMETER_HEADER_SIZE - _dataValidUntilPos;
        // INSTRUCTION PARAMETER HEADER IS COMPLETE
        // Returns size needed to reconstruct instruction parameter
        paramHeader = (instructionParameterHeader_t *)(((char *)_header) + paramHeaderOffset);
        if (_dataValidUntilPos < paramHeaderOffset + _INSTRUCTION_PARAMETER_HEADER_SIZE + paramHeader->parameterSize)
            return paramHeaderOffset + _INSTRUCTION_PARAMETER_HEADER_SIZE + paramHeader->parameterSize - _dataValidUntilPos;
        paramHeaderOffset += _INSTRUCTION_PARAMETER_HEADER_SIZE + paramHeader->parameterSize;
    }
    // INSTRUCTION IS COMPLETE
    return 0;
}

//
// Return a constant reference on raw instruction data
//
const QByteArray &InstructionBuffer::getData() const
{
    return _data;
}

//
// Return transmitter id
// Note: See Note in `void InstructionBuffer::setPeerId()`
//
quint64 InstructionBuffer::getPeerId() const
{
    return _peerId;
}

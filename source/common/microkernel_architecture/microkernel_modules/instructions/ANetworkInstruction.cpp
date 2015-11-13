#include "ANetworkInstruction.hpp"

#include <QDebug>

ANetworkInstruction::ANetworkInstruction()
    : AInstruction()
{
}

ANetworkInstruction::ANetworkInstruction(const ANetworkInstruction &o)
    : AInstruction(o), _dataValidUntilPos(o._dataValidUntilPos)
{
}

ANetworkInstruction::ANetworkInstruction(const QByteArray &data)
    : AInstruction(data), _dataValidUntilPos(data.size())
{
}

ANetworkInstruction::~ANetworkInstruction()
{
}

//
//
//
void ANetworkInstruction::setRawData(const QByteArray &rawData)
{
    _data = rawData;
    _ensureMinimumDataSize();
    _setPointerToData();
}

void ANetworkInstruction::append(const QByteArray &data)
{
    _append(data, _dataValidUntilPos);
}

void ANetworkInstruction::append(const QByteArray &data, int pos)
{
    _append(data, pos);
}

void ANetworkInstruction::_append(const QByteArray &data, int pos)
{
    QByteArray dataBegin(_data.left(pos));

    _dataValidUntilPos += data.size();
    _data = dataBegin + data;
    _ensureMinimumDataSize();
    _setPointersToData();
}

void ANetworkInstruction::setPeerId(quint64 peerId)
{
    _peerId = peerId;
}

int ANetworkInstruction::getNextReadSize() const
{
    if (_dataValidUntilPos < _INSTRUCTION_HEADER_SIZE)
    {
        qDebug() << Q_FUNC_INFO << "0" << "ret=" << (_INSTRUCTION_HEADER_SIZE - _dataValidUntilPos);
        return _INSTRUCTION_HEADER_SIZE - _dataValidUntilPos;
    }
    else
    {
        if (_header->numberOfParameters == 0)
        {
            qDebug() << Q_FUNC_INFO << "1" << "ret=" << 0;
            return 0;
        }
        else
        {
            if (_dataValidUntilPos < _INSTRUCTION_HEADER_SIZE + _INSTRUCTION_PARAMETER_HEADER_SIZE)
            {
                qDebug() << Q_FUNC_INFO << "2" << "ret=" << (_INSTRUCTION_HEADER_SIZE + _INSTRUCTION_PARAMETER_HEADER_SIZE - _dataValidUntilPos);
                return _INSTRUCTION_HEADER_SIZE + _INSTRUCTION_PARAMETER_HEADER_SIZE - _dataValidUntilPos;
            }
            else
            {
                // consider only one parameter for the moment
                instructionParameterHeader_t *parameterHeader = NULL;

                parameterHeader = (instructionParameterHeader_t *)_parametersData;
                if (_dataValidUntilPos < _INSTRUCTION_HEADER_SIZE + _INSTRUCTION_PARAMETER_HEADER_SIZE + parameterHeader->parameterSize)
                {
                    qDebug() << Q_FUNC_INFO << "3" << "ret=" << (_INSTRUCTION_HEADER_SIZE + _INSTRUCTION_PARAMETER_HEADER_SIZE + parameterHeader->parameterSize - _dataValidUntilPos);
                    return _INSTRUCTION_HEADER_SIZE + _INSTRUCTION_PARAMETER_HEADER_SIZE + parameterHeader->parameterSize - _dataValidUntilPos;
                }
                else
                {
                    qDebug() << Q_FUNC_INFO << "4" << "ret=" << 0;
                    return 0;
                }
            }
        }
    }
}

const QByteArray &ANetworkInstruction::getRawData() const
{
    return _data;
}

void ANetworkInstruction::_setPointersToData()
{
    _setPointerToData();
    _parametersData = _header->numberOfParameters == 0 ? NULL : (instructionParameterHeader_t *)(&_data.data()[_FIRST_PARAMETER_OFFSET]);
}

quint64 ANetworkInstruction::getPeerId() const
{
    return _peerId;
}

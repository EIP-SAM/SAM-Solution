#ifndef ANETWORK_MANAGER_HPP_
# define ANETWORK_MANAGER_HPP_

# include "AFunctionality.hpp"
# include "InstructionBuffer.hpp"
# include <QDebug>

class ANetworkManager : public AFunctionality
{
    Q_OBJECT

public:
    ANetworkManager(bool threaded);
    virtual ~ANetworkManager();

protected:
    template<class Socket>
    bool _read(InstructionBuffer *instruction, Socket &socket, qint64 &bytesAvailable)
    {
        qint64 readSize = -1, ret = -1;
        QByteArray buffer;

        if (bytesAvailable <= instruction->getNextReadSize())
            readSize = bytesAvailable;
        else if (bytesAvailable > instruction->getNextReadSize())
            readSize = instruction->getNextReadSize();
        buffer.resize(readSize);
        if ((ret = socket.read(buffer.data(), readSize)) == -1)
        {
            qDebug() << "Error: An error occured while trying to read";
            return false;
        }
        else if (ret == 0)
        {
            qDebug() << "Warning: Trying to read more data than available";
            return false;
        }
        buffer.resize(ret);
        *instruction << buffer;
        bytesAvailable -= ret;
        qDebug() << "Had read" << ret << "bytes";
        qDebug() << buffer;
        return true;
    }

    template<class Socket>
    bool _write(InstructionBuffer *instruction, Socket &socket)
    {
        QByteArray buffer = instruction->getData();
        qint64 writtenSize = 0, ret = 0;

        while (writtenSize != instruction->getData().size())
        {
            if ((ret = socket.write(buffer, buffer.size())) == -1)
            {
                qDebug() << "Error: An error occured while trying to write";
                return false;
            }
            else if (ret == 0)
            {
                qDebug() << "Warning: Trying to write too much data";
                return false;
            }
            writtenSize += ret;
            if (writtenSize < ret)
                buffer = buffer.left(ret);
        }
        return true;
    }

    void _finalizeReceivedInstruction(InstructionBuffer *, quint64);
    bool _instructionPushedIsValid(InstructionBuffer *);

    virtual void _setPeerInputBuffer(InstructionBuffer *, quint64) = 0;
    virtual InstructionBuffer *_getPeerInputBuffer(quint64) const = 0;
};

#endif // !ANETWORK_MANAGER_HPP_

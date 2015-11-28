#include "ANetworkManager.hpp"
#include "MainController.hpp"

ANetworkManager::ANetworkManager(bool threaded)
    : AFunctionality(NETWORK_MANAGER, threaded)
{
}

ANetworkManager::~ANetworkManager()
{
}

void ANetworkManager::_finalizeReceivedInstruction(InstructionBuffer *instruction, quint64 peerId)
{
    if (!instruction->getNextReadSize())
    {
        if (instruction->finalizeFilling())
        {
            AFunctionality::eType fctType = mainController->getFunctionalityType(instruction->getFinalReceiver());

            if (mainController->getProgId() == instruction->getTransmitterProgId() ||
                fctType == AFunctionality::MICROKERNEL || fctType == AFunctionality::INTERNAL)
            {
                delete instruction;
                qDebug() << "Error: Malicious instruction received; Instruction deleted";
            }
            else
                mainController->pushInstruction(instruction);
        }
        else
        {
            delete instruction;
            qDebug() << "Error: Malformed instruction received; Instruction deleted";
        }
        _setPeerInputBuffer(NULL, peerId);
    }
}

bool ANetworkManager::_instructionPushedIsValid(InstructionBuffer *instruction)
{
    if (!instruction)
    {
        qDebug() << "Error: Bad news, there is no instruction in the queue";
        return false;
    }
    if (instruction->getTransmitterProgId() != mainController->getProgId())
    {
        qDebug() << "Error: Trying to send a malicious instruction; Instruction deleted";
        delete instruction;
        return false;
    }
    return true;
}

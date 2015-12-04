#include "StatisticManager.hpp"
#include "AInstruction.hpp"
#include <QDebug>

const StatisticManager::instructionHandler StatisticManager::_handlerPointers[] =
{
    &StatisticManager::instructionHandlerExample
};

StatisticManager::StatisticManager()
    : AFunctionality(STATISTIC_MANAGER, true)
{
}

StatisticManager::~StatisticManager()
{
}

void StatisticManager::instructionHandlerExample(AInstruction *instruction)
{
    (void)instruction;
    qDebug() << Q_FUNC_INFO;
}

void StatisticManager::_run()
{
    AInstruction *instruction = NULL;

    qDebug() << Q_FUNC_INFO;
    while (42)
    {
        if ((instruction = _popInstruction()))
        {
            qDebug() << Q_FUNC_INFO << ": New instruction received";
            if (instruction->getInstructionCode() < sizeof(_handlerPointers))
                (this->*_handlerPointers[instruction->getInstructionCode()])(instruction);
            delete instruction;
            instruction = NULL;
        }
        QThread::msleep(30);
    }
}

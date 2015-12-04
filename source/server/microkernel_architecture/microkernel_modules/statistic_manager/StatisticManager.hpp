#ifndef STATISTIC_MANAGER_HPP_
#define STATISTIC_MANAGER_HPP_

# include "AFunctionality.hpp"

class StatisticManager : public AFunctionality
{
    Q_OBJECT

private:
    typedef void (StatisticManager::*instructionHandler)(AInstruction *);

    enum eInstruction : unsigned int
    {
        EXAMPLE = 0
    };

    static const instructionHandler _handlerPointers[];

public:
    StatisticManager();
    ~StatisticManager();

    void instructionHandlerExample(AInstruction *);

protected slots:
    virtual void _run();
};

#endif // !STATISTIC_MANAGER_HPP_

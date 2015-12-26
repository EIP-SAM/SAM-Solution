#ifndef TEST_INSTRUCTION_CONNECT_HPP_
# define TEST_INSTRUCTION_CONNECT_HPP_

# include "Connect.hpp"
# include <QtTest/QtTest>

class TestInstructionConnect : public QObject
{
    Q_OBJECT

public:
    TestInstructionConnect();
    virtual ~TestInstructionConnect();

private slots:
    void TestConstructObject();
};

#endif // !TEST_INSTRUCTION_CONNECT_HPP_

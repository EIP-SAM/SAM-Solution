#ifndef TEST_INSTRUCTION_DISCONNECT_HPP_
# define TEST_INSTRUCTION_DISCONNECT_HPP_

# include "Disconnect.hpp"
# include <QtTest/QtTest>

class TestInstructionDisconnect : public QObject
{
    Q_OBJECT

public:
    TestInstructionDisconnect();
    ~TestInstructionDisconnect();

private slots:
    void TestConstructObject();
};

#endif // !TEST_INSTRUCTION_DISCONNECT_HPP_

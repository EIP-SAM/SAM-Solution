#ifndef TEST_INSTRUCTION_CREATE_USER_HPP_
# define TEST_INSTRUCTION_CREATE_USER_HPP_

# include "CreateUser.hpp"
# include <QtTest/QtTest>

class TestInstructionCreateUser : public QObject
{
    Q_OBJECT

public:
    TestInstructionCreateUser();
    virtual ~TestInstructionCreateUser();

private slots:
    void TestConstructObject();
};

#endif // !TEST_INSTRUCTION_CREATE_USER_HPP_

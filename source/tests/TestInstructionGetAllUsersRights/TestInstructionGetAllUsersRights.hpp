#ifndef TEST_INSTRUCTION_GET_ALL_USERS_RIGHTS_HPP_
# define TEST_INSTRUCTION_GET_ALL_USERS_RIGHTS_HPP_

# include "GetAllUsersRights.hpp"
# include <QtTest/QtTest>

class TestInstructionGetAllUsersRights : public QObject
{
    Q_OBJECT

public:
    TestInstructionGetAllUsersRights();
    ~TestInstructionGetAllUsersRights();

private slots:
    void TestConstructObject();
};

#endif // !TEST_INSTRUCTION_GET_ALL_USERS_RIGHTS_HPP_

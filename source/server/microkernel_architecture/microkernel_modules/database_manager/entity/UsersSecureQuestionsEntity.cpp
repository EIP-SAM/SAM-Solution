#include "UsersSecureQuestions.hpp"

UsersSecureQuestionsEntity::UsersSecureQuestionsEntity()
{
    this->_table = "UsersSecureQuestions";
    this->id = -1;
}

UsersSecureQuestionsEntity::~UsersSecureQuestionsEntity()
{

}

unsigned int UsersSecureQuestionsEntity::getId() const
{
    return this->id;
}

void UsersSecureQuestionsEntity::setId(unsigned int id)
{
    this->id = id;
}

unsigned int UsersSecureQuestionsEntity::getUserId() const
{
    return this->userId;
}

void UsersSecureQuestionsEntity::setUserId(unsigned int userId)
{
    this->userId = userId;
}

unsigned int UsersSecureQuestionsEntity::getQuestionId() const
{
    return this->questionId;
}

void UsersSecureQuestionsEntity::setQuestionId(unsigned int questionId)
{
    this->questionId = questionId;
}

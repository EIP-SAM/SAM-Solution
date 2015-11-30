#include "SecureQuestionEntity.hpp"

SecureQuestionsEntity::SecureQuestionsEntity()
{
    this->_table = "SecureQuestions";
    this->id = -1;
}

SecureQuestionsEntity::~SecureQuestionsEntity()
{

}

unsigned int SecureQuestionsEntity::getId() const
{
    return this->id;
}

void SecureQuestionsEntity::setId(unsigned int id)
{
    this->id = id;
}

std::string SecureQuestionsEntity::getQuestion() const
{
    return this->question;
}

void SecureQuestionsEntity::setQuestion(std::string question)
{
    this->question = question;
}

#ifndef USERSSECUREQUESTIONS_ENTITY_HPP_
# define USERSSECUREQUESTIONS_ENTITY_HPP_

# include <iostream>
# include "Entity.hpp"
# include "UsersEntity.hpp"
# include "SecureQuestionsEntity.hpp"

class UsersSecureQuestionsEntity : public Entity
{
    Q_OBJECT

    Q_PROPERTY(unsigned int id READ getId WRITE setId)
    Q_PROPERTY(unsigned int userId READ getUserId WRITE setUserId)
    Q_PROPERTY(unsigned int questionId READ getQuestionId WRITE setQuestionId)
    Q_PROPERTY(QString answer READ getAnswer WRITE setAnswer)

public:
    UsersSecureQuestionsEntity();
    virtual ~UsersSecureQuestionsEntity();

protected:
    unsigned int id;
    unsigned int userId;
    unsigned int quesionId;
    std::string answer;

public:
    unsigned int getId() const;
    void setId(unsigned int);
    unsigned int getUserId() const;
    void setUserId(unsigned int);
    unsigned int getQuestionId() const;
    void setQuestionId(unsigned int);
    std::string getAnswer() const;
    void setAnswer(std::string);

#endif // SECUREQUESTIONS_ENTITY_HPP_


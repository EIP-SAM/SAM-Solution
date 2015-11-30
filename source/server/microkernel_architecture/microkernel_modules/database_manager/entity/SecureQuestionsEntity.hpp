#ifndef SECUREQUESTIONS_ENTITY_HPP_
# define SECUREQUESTIONS_ENTITY_HPP_

# include <iostream>
# include "Entity.hpp"

class SecureQuestionsEntity : public Entity
{
    Q_OBJECT

    Q_PROPERTY(unsigned int id READ getId WRITE setId)
    Q_PROPERTY(QString question READ getQuestion WRITE setQuestion)

public:
    SecureQuestionsEntity();
    virtual ~SecureQuestionsEntity();

protected:
    unsigned int id;
    std::string question;

public:
    unsigned int getId() const;
    void setId(unsigned int);
    std::string getQuestion() const;
    void setQuestion(std::string);
};

#endif // SECUREQUESTIONS_ENTITY_HPP_

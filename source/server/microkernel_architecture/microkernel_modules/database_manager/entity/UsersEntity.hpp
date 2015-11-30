#ifndef USERS_ENTITY_HPP_
# USERS_ENTITY_HPP_

# include <iostream>
# include <QDateTime>
# include "Entity.hpp"

class UsersEntity : public Entity
{
    Q_OBJECT

    Q_PROPERTY(unsigned int id READ getId WRITE setId)
    Q_PROPERTY(QString login READ getLogin WRITE setLogin)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword)
    Q_PROPERTY(int rights READ getRights WRITE setRights)
    Q_PROPERTY(bool isActive READ getIsActive WRITE setIsActive)

public:
    UsersEntity();
    virtual ~UsersEntity();

protected:
    unsigned int id;
    std::string login;
    std::string password;
    QDateTime dateRegister;
    int rights;
    bool isActive;

public:
    unsigned int getId() const;
    void setId(unsigned int);
    std::string getLogin() const;
    void setLogin(std::string);
    std::string getPassword() const;
    void setPassword(std::string);
    QDateTime getDateRegister() const;
    void setDateRegister(QDateTime);
    int getRights() const;
    void setRights(int);
    bool getIsActive() const;
    void setIsActive(bool);
};

#endif // USERS_ENTITY_HPP_

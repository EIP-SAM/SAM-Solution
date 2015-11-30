#include "UsersEntity.hpp"

UsersEntity::UsersEntity() : Entity()
{
    this->_table = "Users";
    this->id = -1;
}

UsersEntity::~UsersEntity()
{

}

unsigned int UsersEntity::getId() const
{
    return this->id;
}

void UsersEntity::setId(unsigned int id)
{
    this->id = id;
}

std::string UsersEntity::getLogin() const
{
    return this->login;
}

void UsersEntity::setLogin(std::string login)
{
    this->login = login;
}

std::string UsersEntity::getPassword() const
{
    return this->password;
}

void UsersEntity::setPassword(std::string password)
{
    this->password = password;
}

QDateTime UsersEntity::getDateRegister() const
{
    return this->dateRegister;
}

void UsersEntity::setDateRegister(QDateTime dateRegister)
{
    this->dateRegister = dateRegister;
}

int UsersEntity::getRights() const
{
    return this->rights;
}

void UsersEntity::setRights(int rights)
{
    this->rights = rights;
}

bool UsersEntity::getIsActive() const
{
    return this->isActive;
}

void UsersEntity::setIsActive(bool isActive)
{
    this->isActive = isActive;
}

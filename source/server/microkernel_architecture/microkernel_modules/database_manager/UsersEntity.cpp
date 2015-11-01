#include	"UsersEntity.hpp"

UsersEntity::UsersEntity()
{
  this->table = "Users";
}

UsersEntity::~UsersEntity()
{
}

int		UsersEntity::getId() const
{
  return this->id;
}

void		UsersEntity::setId(int newId)
{
  this->id = newId;
}

std::string	UsersEntity::getLogin() const
{
  return this->login;
}

void		UsersEntity::setLogin(std::string newLogin)
{
  this->login = newLogin;
}

std::string	UsersEntity::getPassword() const
{
  return this->password;
}

void		UsersEntity::setPassword(std::string newPassword)
{
  this->password = newPassword;
}


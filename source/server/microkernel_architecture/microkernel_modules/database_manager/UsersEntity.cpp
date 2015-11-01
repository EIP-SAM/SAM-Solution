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

QString	UsersEntity::getLogin() const
{
  return this->login;
}

void		UsersEntity::setLogin(QString newLogin)
{
  this->login = newLogin;
}

QString	UsersEntity::getPassword() const
{
  return this->password;
}

void		UsersEntity::setPassword(QString newPassword)
{
  this->password = newPassword;
}


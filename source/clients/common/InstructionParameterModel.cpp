#include	"InstructionParameterModel.hpp"

InstructionParameterModel::InstructionParameterModel()
{
}

void		InstructionParameterModel::setType(int type)
{
  _type = type;
}

int		InstructionParameterModel::getType() const
{
  return (_type);
}

void		InstructionParameterModel::setParam(const std::string &param)
{
  _param = param;
}

std::string	InstructionParameterModel::getParam() const
{
  return (_param);
}

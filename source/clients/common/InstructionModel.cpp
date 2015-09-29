#include				"InstructionModel.hpp"

InstructionModel::InstructionModel()
{
}

InstructionModel::~InstructionModel()
{
  for (std::vector<InstructionParameterModel>::iterator it = _param.begin();
       it != _param.end(); ++it)
    {
      delete(*it);
    }
}

void					InstructionModel::setInstructionCode(int instructionCode)
{
  _instructionCode = instructionCode;
}

int					InstructionModel::getInstructionCode() const
{
  return (_instructionCode);
}

void					InstructionModel::setReturnType(int returnType)
{
  _returnType = returnType;
}

int					InstructionModel::getReturnType() const
{
  return (_returnType);
}

void					InstructionModel::setIsSynchrone(int isSynchrone)
{
  _isSynchrone = isSynchrone;
}

int					InstructionModel::getIsSynchrone() const
{
  return (_isSynchrone);
}

void					InstructionModel::setParam(const
						   std::vector<InstructionParameterModel> &param)
{
  _param.push_back(param);
}

std::vector<InstructionParameterModel>	getParam() const
{
  return (_param);
}

#ifndef		INSTRUCTION_PARAMETER_MODEL_HPP_
# define	INSTRUCTION_PARAMETER_MODEL_HPP_

class		InstructionParameterModel
{
public:
  InstructionParameterModel();
  ~InstructionParameterModel() {};
  void		setType(int type);
  int		getType() const;
  void		setParam(const std::string &param);
  std::string	getParam() const;

private:
  int		_type;
  std::string	_param;
};

#endif		/* !INSTRUCTION_PARAMETER_MODEL_HPP_ */

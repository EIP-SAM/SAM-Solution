#ifndef						INSTRUCTION_MODEL_HPP_
# define					INSTRUCTION_MODEL_HPP_

# include					"InstructionParameterModel.hpp"

class						InstructionModel
{
public:
  InstructionModel();
  ~InstructionModel();
  void						setInstructionCode(int instructionCode);
  int						getInstructionCode() const;
  void						setReturnType(int returnType);
  int						getReturnType() const;
  void						setIsSynchrone(int isSynchrone);
  bool						getIsSynchrone() const;
  void						setParam(const std::vector<InstructionParameterModel>
							 &param);
  std::vector<InstructionParameterModel>	getParam() const;

private:
  int						_instructionCode;
  int						_returnType;
  bool						_isSynchrone;
  std::vector<InstructionParameterModel>	_param;
};

#endif		/* !INSTRUCTION_MODEL_HPP_ */

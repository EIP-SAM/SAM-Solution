#ifndef						AINSTRUCTION_HPP_
# define					AINSTRUCTION_HPP_

# include					<QByteArray>

class						AInstruction
{
public:
  AInstruction();
  ~AInstruction();
  void						setInstructionCode(int instructionCode);
  int						getInstructionCode() const;
  void						setReturnType(int returnType);
  int						getReturnType() const;
  void						setIsSynchrone(bool isSynchrone);
  bool						getIsSynchrone() const;
private:
  int						*_instructionCode;
  int						*_returnType;
  bool						*_isSynchrone;
  QByteArray					*_byteArray;
};

#endif		/* !AINSTRUCTION_HPP_ */

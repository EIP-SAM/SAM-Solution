#ifndef ANETWORK_INSTRUCTION_HPP_
# define ANETWORK_INSTRUCTION_HPP_

# include "AInstructionModel.hpp"

class ANetworkInstruction : public AInstructionModel
{
public:
  ANetworkInstruction();
  ANetworkInstruction(QByteArray *byteArray);
  ~ANetworkInstruction();
  void _init();
  void setInstructionCode(int instructionCode);
  int getInstructionCode() const;
  void setReturnType(int returnType);
  int getReturnType() const;
  void setIsSynchrone(bool isSynchrone);
  bool getIsSynchrone() const;
private:
  int *_instructionCode;
  int *_returnType;
  bool *_isSynchrone;
};

#endif // !ANETWORK_INSTRUCTION_HPP_

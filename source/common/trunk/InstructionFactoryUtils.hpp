#ifndef				INSTRUCTIONFACTORYUTILS_HPP_
# define			INSTRUCTIONFACTORYUTILS_HPP_

# include			"AInstructionModel.hpp"

class				InstructionFactoryUtils
{
public:
  InstructionFactoryUtils();
  ~InstructionFactoryUtils();

  static AInstructionModel	create(int argInstructionCode, int argReturnType, bool argIsSynchrone);
  static AInstructionModel	create(QByteArray *byteArray);
  
};

#endif				/* !INSTRUCTIONFACTORYUTILS_HPP_ */

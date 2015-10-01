#ifndef		TEST_A_INSTRUCTION_MODEL_HPP_
# define	TEST_A_INSTRUCTION_MODEL_HPP_

#include	<QtTest/QtTest>
#include	"AInstructionModel.hpp"

class		TestAInstructionModel : public QObject
{
  Q_OBJECT
public:
  TestAInstructionModel();
  virtual	~TestAInstructionModel();

private slots:
  void		_init();
  void		ptrTest();
};

#endif		/* !TEST_A_INSTRUCTION_MODEL_HPP_ */

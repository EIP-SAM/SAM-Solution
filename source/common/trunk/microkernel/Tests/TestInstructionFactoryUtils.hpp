#ifndef		TEST_INSTRUCTION_FACTORY_UTILS_HPP_
# define	TEST_INSTRUCTION_FACTORY_UTILS_HPP_

# include	<QtTest/QtTest>
# include	"InstructionFactoryUtils.hpp"

class		TestInstructionFactoryUtils : public QObject
{
  Q_OBJECT

public:
  TestInstructionFactoryUtils();
  virtual ~TestInstructionFactoryUtils();

private slots:
  void		TestCreate();
  void		TestCreateArray();
};

#endif		/* !TEST_INSTRUCTION_FACTORY_UTILS_HPP_ */

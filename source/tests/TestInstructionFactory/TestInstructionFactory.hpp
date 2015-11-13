#ifndef TEST_INSTRUCTION_FACTORY_HPP_
# define TEST_INSTRUCTION_FACTORY_HPP_

# include <QtTest/QtTest>
# include "InstructionFactory.hpp"

class TestInstructionFactory : public QObject
{
  Q_OBJECT

public:
  TestInstructionFactory();
  virtual ~TestInstructionFactory();

private slots:
  void _TestCreate();
  void _TestCreateArray();
};

#endif // !TEST_INSTRUCTION_FACTORY_HPP_

#ifndef TEST_A_NETWORK_INSTRUCTION_HPP_
# define TEST_A_NETWORK_INSTRUCTION_HPP_

# include <QtTest/QtTest>
# include "ANetworkInstruction.hpp"

class TestANetworkInstruction : public QObject
{
  Q_OBJECT

public:
  TestANetworkInstruction();
  virtual ~TestANetworkInstruction();

private slots:
  void _init();
  void ptrTest();
};

#endif // !TEST_A_NETWORK_INSTRUCTION_HPP_

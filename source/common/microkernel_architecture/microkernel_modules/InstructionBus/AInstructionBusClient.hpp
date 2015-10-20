#ifndef AINSTRUCTIONBUSCLIENT_HPP_
#define AINSTRUCTIONBUSCLIENT_HPP_

# include <QQueue>

class AInstruction;

class AInstructionBusClient
{
public:  
  typedef enum eClientId
    {
      INVALID = 0
    }eClientId;
  
  AInstructionBusClient(eClientId, QQueue<AInstruction *>);
  virtual ~AInstructionBusClient();
  eClientId getClientId() const;
  void setClientId(eClientId);
  QQueue<AInstruction *> getInstructions() const;
  
  void setInstructions(QQueue<AInstruction *>);
  void pushInstruction(AInstruction *);
  bool _hasInstructions();
  AInstruction * _popInstruction();
  
private:
  eClientId _clientId;
  QQueue<AInstruction *> _instructions;
};

#endif // !AINSTRUCTIONBUSCLIENT_HPP_

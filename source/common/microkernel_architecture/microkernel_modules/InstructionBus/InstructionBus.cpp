#include "InstructionBus.hpp"

InstructionBus::InstructionBus(QThread *thread, QMap<AInstructionBusClient::eClientId, AInstructionBusClient *>clientRegister,
                       QMap<AInstructionBusClient *, QQueue<AInstruction *> *>clientsInstructions)
{
    // ctor
    this->_thread = thread;
    this->_clientRegister = clientRegister;
    this->_clientsInstructions = clientsInstructions;
}

InstructionBus::~InstructionBus()
{
    // dtor
}

QThread *InstructionBus::getThread() const
{
    return this->_thread;
}

void InstructionBus::setThread(QThread *thread)
{
    this->_thread = thread;
}

QMap<AInstructionBusClient::eClientId, AInstructionBusClient *> InstructionBus::getClientRegister() const
{
    return this->_clientRegister;
}

void InstructionBus::setClientRegister(QMap<AInstructionBusClient::eClientId, AInstructionBusClient *> clientRegister)
{
    this->_clientRegister = clientRegister;
}

QMap<AInstructionBusClient *, QQueue<AInstruction *> *>InstructionBus::getClientsInstructions() const
{
    return this->_clientsInstructions;
}

void InstructionBus::setClientsInstructions(QMap<AInstructionBusClient *, QQueue<AInstruction *> *>clientsInstructions)
{
    this->_clientsInstructions = clientsInstructions;
}

void InstructionBus::init()
{
    // demarre un nouveau thread dans l'InstructionBus
    this->_thread->start();
}

void InstructionBus::run()
{
    // boucle infinie de dispatch des instructions
}

void InstructionBus::_register(AInstructionBusClient::eClientId clientId, AInstructionBusClient *instructionBusClient)
{
    // set le AInstructionBusClient et son eClientId dans la map _clientRegister
    this->_clientRegister.insert(clientId, instructionBusClient);
}

void InstructionBus::pushInstruction(AInstruction *instruction)
{
    // (appel executé depuis un autre thread -> protection via QMutex) push une AInstruction dans la queue
    int busInMap = 0;

    if (!this->_clientsInstructions.empty())
      {
        QMap<AInstructionBusClient *, QQueue<AInstruction *> *>::const_iterator i = this->_clientsInstructions.find(instruction->getTransmitter());
        if (i != this->_clientsInstructions.end())
	  {
            busInMap = 1;
	    i.value()->enqueue(instruction);
	  }
      }
    if (busInMap == 0)
      {
        QQueue<AInstruction *> q;
        q.enqueue(instruction);
        this->_clientsInstructions.insert(instruction->getTransmitter(), &q);
      }
}

void InstructionBus::_dispatchInstruction(AInstruction *instruction)
{
    // prend la plus vieille instruction dans _clientsInstruction et le dispatch dans l'AInstructionBusClient correspondante
    AInstructionBusClient *bus = instruction->getTransmitter();
    AInstructionBusClient::eClientId cId = bus->getClientId();
    QMap<AInstructionBusClient::eClientId, AInstructionBusClient *>::const_iterator i = this->_clientRegister.find(cId);

    if (i == this->_clientRegister.end())
        std::cerr << "Error: missing instruction in the client register queue." << std::endl;
    else
        i.value()->pushInstruction(instruction);
}

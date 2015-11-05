#include "InstructionBus.hpp"

InstructionBus::InstructionBus(QThread *thread,
                               QMap<AInstructionBusClient::eClientId, AInstructionBusClient *>clientRegister,
                               QMap<AInstructionBusClient *, QQueue<AInstruction *> *>clientsInstructions)
    : _thread(thread), _clientRegister(clientRegister), _clientsInstructions(clientsInstructions)
{
}

InstructionBus::~InstructionBus()
{
}

//
// demarre un nouveau thread dans l'InstructionBus
//
void InstructionBus::init()
{
    _thread->start();
}

//
// boucle infinie de dispatch des instructions
//
void InstructionBus::run()
{
}

//
// set le AInstructionBusClient et son eClientId dans la map _clientRegister
//
void InstructionBus::_register(AInstructionBusClient::eClientId clientId, AInstructionBusClient *instructionBusClient)
{
    _clientRegister.insert(clientId, instructionBusClient);
}

//
// (appel execut depuis un autre thread -> protection via QMutex) push une AInstruction dans la queue
//
void InstructionBus::pushInstruction(AInstruction *instruction)
{
    int busInMap = 0;

    if (!_clientsInstructions.empty())
    {
        QMap<AInstructionBusClient *, QQueue<AInstruction *> *>::const_iterator i = this->_clientsInstructions.find(instruction->getTransmitter());

        if (i != _clientsInstructions.end())
        {
            busInMap = 1;
            i.value()->enqueue(instruction);
        }
    }
    if (busInMap == 0)
    {
        QQueue<AInstruction *> q;

        q.enqueue(instruction);
        _clientsInstructions.insert(instruction->getTransmitter(), &q);
    }
}

//
// prend la plus vieille instruction dans _clientsInstruction et le dispatch dans l'AInstructionBusClient correspondante
//
void InstructionBus::_dispatchInstruction(AInstruction *instruction)
{
    AInstructionBusClient *bus = instruction->getTransmitter();
    AInstructionBusClient::eClientId cId = bus->getClientId();
    QMap<AInstructionBusClient::eClientId, AInstructionBusClient *>::const_iterator i = _clientRegister.find(cId);

    if (i == _clientRegister.end())
        std::cerr << "Error: missing instruction in the client register queue." << std::endl;
    else
        i.value()->pushInstruction(instruction);
}

void InstructionBus::setThread(QThread *thread)
{
    _thread = thread;
}

void InstructionBus::setClientRegister(QMap<AInstructionBusClient::eClientId, AInstructionBusClient *> clientRegister)
{
    _clientRegister = clientRegister;
}

void InstructionBus::setClientsInstructions(QMap<AInstructionBusClient *, QQueue<AInstruction *> *>clientsInstructions)
{
    _clientsInstructions = clientsInstructions;
}

QThread *InstructionBus::getThread() const
{
    return _thread;
}

QMap<AInstructionBusClient::eClientId, AInstructionBusClient *> InstructionBus::getClientRegister() const
{
    return _clientRegister;
}

QMap<AInstructionBusClient *, QQueue<AInstruction *> *>InstructionBus::getClientsInstructions() const
{
    return _clientsInstructions;
}

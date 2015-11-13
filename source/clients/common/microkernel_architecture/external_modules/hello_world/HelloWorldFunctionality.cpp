#include "HelloWorldFunctionality.hpp"
#include "MainController.hpp"
#include "InstructionBuffer.hpp"
#include <QDebug>

HelloWorldFunctionality::HelloWorldFunctionality()
    : AFunctionality(HELLO_WORLD_BAR)
{
    // CLIENT TEST FUNCTIONALITY
}

void HelloWorldFunctionality::_run()
{
    AInstruction *inputInstruction = NULL;
    InstructionBuffer *outputInstruction = NULL;

    qDebug() << Q_FUNC_INFO;
    outputInstruction = new InstructionBuffer();
    outputInstruction->setLocalTransmitter(this);
    outputInstruction->setFinalReceiver(HELLO_WORLD_FOO);
    mainController->getInstructionBus().pushInstruction(outputInstruction);
    outputInstruction = NULL;
    while (42)
    {
        if ((inputInstruction = _popInstruction()))
        {
            qDebug() << Q_FUNC_INFO << ": Instruction received !";
            delete inputInstruction;
            inputInstruction = NULL;
        }
        QThread::msleep(30);
    }
}

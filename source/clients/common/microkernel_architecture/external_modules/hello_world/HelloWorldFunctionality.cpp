#include "HelloWorldFunctionality.hpp"
#include "MainController.hpp"
#include "ANetworkInstruction.hpp"
#include <QDebug>

HelloWorldFunctionality::HelloWorldFunctionality()
    : AFunctionality(HELLO_WORLD_BAR)
{
    // CLIENT TEST FUNCTIONALITY
}

void HelloWorldFunctionality::run()
{
    AInstruction *inputInstruction = NULL;
    ANetworkInstruction *outputInstruction = NULL;

    qDebug() << Q_FUNC_INFO;
    outputInstruction = new ANetworkInstruction();
    outputInstruction->setLocalTransmitter(this);
    outputInstruction->setFinalReceiver(HELLO_WORLD_FOO);
    mainController->getInstructionBus().pushInstruction(outputInstruction);
    outputInstruction = NULL;
    while (42)
    {
        if ((inputInstruction = _popInstruction()))
        {
            qDebug() << Q_FUNC_INFO << ": Instruction received !";
            qDebug() << inputInstruction->getRawData();
            delete inputInstruction;
            inputInstruction = NULL;
        }
        QThread::msleep(30);
    }
}

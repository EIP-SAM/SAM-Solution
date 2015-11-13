#include "HelloWorldFunctionality.hpp"
#include "MainController.hpp"
#include "InstructionBuffer.hpp"
#include <QDebug>

HelloWorldFunctionality::HelloWorldFunctionality()
    : AFunctionality(HELLO_WORLD_FOO)
{
    // SERVER TEST FUNCTIONALITY
}

void HelloWorldFunctionality::_run()
{
    AInstruction *inputInstruction = NULL;
    InstructionBuffer *inputInstruction2 = NULL;
    InstructionBuffer *outputInstruction = NULL;

    qDebug() << Q_FUNC_INFO;
    while (42)
    {
        if ((inputInstruction = _popInstruction()))
        {
            qDebug() << Q_FUNC_INFO << ": Instruction received !";
            inputInstruction2 = static_cast<InstructionBuffer *>(inputInstruction);

            outputInstruction = new InstructionBuffer();
            outputInstruction->setLocalTransmitter(this);
            outputInstruction->setFinalReceiver(HELLO_WORLD_BAR);
            outputInstruction->setPeerId(inputInstruction2->getPeerId());
            mainController->getInstructionBus().pushInstruction(outputInstruction);

            delete inputInstruction;
            inputInstruction = NULL;
            inputInstruction2 = NULL;
            outputInstruction = NULL;
        }
        QThread::msleep(30);
    }
}

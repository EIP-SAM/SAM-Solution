#include "AInstructionModel.hpp"

AInstructionModel::AInstructionModel()
{
    _byteArray = new QByteArray();
}

AInstructionModel::~AInstructionModel()
{
    delete(_byteArray);
}

void AInstructionModel::setByteArray(QByteArray *byteArray)
{
    _byteArray = byteArray;
}

QByteArray *AInstructionModel::getByteArray() const
{
    return (_byteArray);
}

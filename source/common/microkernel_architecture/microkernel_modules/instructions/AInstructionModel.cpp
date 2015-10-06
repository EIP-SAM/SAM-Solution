#include "AInstructionModel.hpp"

AInstructionModel::AInstructionModel()
{
    _init();
}

//
// This constructor create a copy of a QByteArray: pointer and value
//

AInstructionModel::AInstructionModel(QByteArray *byteArray)
{
    int *intPtr;
    bool *boolPtr;
    const char *content;

    _init();

    content = byteArray->constData();
    intPtr = (int*)&(content[INDEX_BYTE_INSTRUCTIONCODE]);
    setInstructionCode(*intPtr);
    intPtr = (int*)&(content[INDEX_BYTE_RETURNTYPE]);
    setReturnType(*intPtr);
    boolPtr = (bool*)&(content[INDEX_BYTE_ISSYNCHRONE]);
    setIsSynchrone(*boolPtr);
}

AInstructionModel::~AInstructionModel()
{
    delete(_byteArray);
}

//
// Stock in the attribut _byteArray pointer to other attributs to define number of bytes
// Add default value to attributs
//

void AInstructionModel::_init()
{
    char *ptr = NULL;

    _byteArray = new QByteArray(CONTENT_BYTE_SIZE, '\0');

    ptr = _byteArray->data();
    _instructionCode = (int *)&(ptr[INDEX_BYTE_INSTRUCTIONCODE]);
    _returnType = (int *)&(ptr[INDEX_BYTE_RETURNTYPE]);
    _isSynchrone = (bool *)&(ptr[INDEX_BYTE_ISSYNCHRONE]);

    setInstructionCode(0);
    setReturnType(0);
    setIsSynchrone(false);
}

void AInstructionModel::setInstructionCode(int instructionCode)
{
    *_instructionCode = instructionCode;
}

int AInstructionModel::getInstructionCode() const
{
    return (*_instructionCode);
}

void AInstructionModel::setReturnType(int returnType)
{
    *_returnType = returnType;
}

int AInstructionModel::getReturnType() const
{
    return (*_returnType);
}

void AInstructionModel::setIsSynchrone(bool isSynchrone)
{
    *_isSynchrone = isSynchrone;
}

bool AInstructionModel::getIsSynchrone() const
{
    return (*_isSynchrone);
}

void AInstructionModel::setByteArray(QByteArray *byteArray)
{
    _byteArray = byteArray;
}

QByteArray *AInstructionModel::getByteArray() const
{
    return (_byteArray);
}

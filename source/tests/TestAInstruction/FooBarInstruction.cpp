#include "FooBarInstruction.hpp"

FooBarInstruction::FooBarInstruction()
{
}

FooBarInstruction::~FooBarInstruction()
{
}

bool FooBarInstruction::init(int foo, const QString& bar)
{
    if (!(_foo = createParameter()) || !(_bar = createParameter()))
        return false;
    _foo->setRawData(QByteArray((const char *)&foo, sizeof(foo)));
    _bar->setRawData(bar.toLocal8Bit());
    return true;
}

void FooBarInstruction::setFoo(int foo)
{
    _foo->setRawData(QByteArray((const char *)&foo, sizeof(foo)));
}

void FooBarInstruction::setBar(const QString &bar)
{
    _bar->setRawData(bar.toLocal8Bit());
}

int FooBarInstruction::getFoo() const
{
    return _foo ? *((const int *)(_foo->getRawData().constData())) : 0;
}

QString FooBarInstruction::getBar() const
{
    return _bar ? QString(_bar->getRawData()) : "";
}

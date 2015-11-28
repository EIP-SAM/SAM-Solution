#include "FooBarInstruction.hpp"
#include <QString>
#include <QtTest>
#include <QDebug>

class TestAInstruction : public QObject
{
    Q_OBJECT

private:
    FooBarInstruction *_foobar = NULL;

public:
    TestAInstruction();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testConstructedParameters();
    void testResetParameters();
};

TestAInstruction::TestAInstruction()
{
}

void TestAInstruction::initTestCase()
{
    _foobar = new FooBarInstruction;
    QVERIFY(_foobar->init(42, "Foo Bar Baz") == true);
}

void TestAInstruction::cleanupTestCase()
{
    delete _foobar;
}

void TestAInstruction::testConstructedParameters()
{
    QVERIFY(_foobar->getFoo() == 42);
    QVERIFY(_foobar->getBar() == "Foo Bar Baz");
}

void TestAInstruction::testResetParameters()
{
    _foobar->setFoo(-21);
    QVERIFY(_foobar->getFoo() == -21);

    _foobar->setBar("Chaud patate!");
    QVERIFY(_foobar->getBar() == "Chaud patate!");
}

QTEST_APPLESS_MAIN(TestAInstruction)

#include "TestAInstruction.moc"

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
    void testCase1();
    void testCase2();
};

TestAInstruction::TestAInstruction()
{
}

void TestAInstruction::initTestCase()
{
    QVERIFY((_foobar = new FooBarInstruction()) != NULL);
    QVERIFY(_foobar->init(42, "Foo Bar Baz") == true);
}

void TestAInstruction::cleanupTestCase()
{
    delete _foobar;
}

void TestAInstruction::testCase1()
{
    QVERIFY(_foobar->getFoo() == 42);
    QVERIFY(_foobar->getBar() == "Foo Bar Baz");
}

void TestAInstruction::testCase2()
{
    _foobar->setFoo(-21);
    QVERIFY(_foobar->getFoo() == -21);

    _foobar->setBar("Chaud patate!");
    QVERIFY(_foobar->getBar() == "Chaud patate!");
}

QTEST_APPLESS_MAIN(TestAInstruction)

#include "TestAInstruction.moc"

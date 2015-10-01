#include  <QtTest/QtTest>
#include  <string>
#include  <iostream>
#include  <fstream>
#include  "../../FileObject.hpp"

//
// UnitTests
//


class TestFileObjectToTest: public QObject
{

Q_OBJECT

public:
TestFileObjectToTest();
virtual ~TestFileObjectToTest();
  private slots:
    void    TestgetPortToTest();
    void    TestgetIpToTest();
    void    TestgetNameFileToTest();
};

TestFileObjectToTest::TestFileObjectToTest()
{
}

TestFileObjectToTest::~TestFileObjectToTest()
{
}

void    TestFileObjectToTest::TestgetPortToTest()
{
	FileObject obj("test");

	obj.setPort(42);
        QCOMPARE(obj.getPort(), 42);
}

void    TestFileObjectToTest::TestgetIpToTest()
{
        FileObject obj("test");

        obj.setIp("42");
        QCOMPARE(obj.getIp(), std::string("42"));
}

void    TestFileObjectToTest::TestgetNameFileToTest()
{
        FileObject obj("test");

        obj.setNameFile("42");
        QCOMPARE(obj.getNameFile(), std::string("42"));
}

QTEST_MAIN(TestFileObjectToTest)
#include "TestFileObjectToTest.moc"


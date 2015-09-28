#include  <QtTest/QtTest>
#include  "../FileManagerUtils.hpp"

//
// 
//


class TestFileManagerUtils: public QObject
{

Q_OBJECT

public:
TestFileManagerUtils();
virtual ~TestFileManagerUtils();
  private slots:
    void    parseFileKeyValue();
};

TestFileManagerUtils::TestFileManagerUtils()
{
}

TestFileManagerUtils::~TestFileManagerUtils()
{
}

void	TestFileManagerUtils::parseFileKeyValue()
{
    QCOMPARE("test", "test");
}

QTEST_MAIN(TestFileManagerUtils)
#include "testfilemanagerutils.moc"

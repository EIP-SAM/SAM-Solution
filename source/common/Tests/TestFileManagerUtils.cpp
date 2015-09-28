#include  <QtTest/QtTest>
#include  <string>
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
	std::string fileConf("sam.conf");
	std::vector<std::string> keyWords;
	keyWords.push_back("port");
	keyWords.push_back("ip");
    	FileManagerUtils *fileManager = new FileManagerUtils;

	std::vector<std::string> ret = fileManager->parseFileKeyValue(fileConf, keyWords);
	printf("%s", keyWords.at(0).c_str());
	QCOMPARE(keyWords.at(0), std::string("192.168.1.2;"));
}

QTEST_MAIN(TestFileManagerUtils)
#include "TestFileManagerUtils.moc"

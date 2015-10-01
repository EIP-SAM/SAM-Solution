#include  <QtTest/QtTest>
#include  <string>
#include  <iostream>
#include  <fstream>
#include  <map>
#include  "../../FileManagerUtils.hpp"

//
// UnitTests
//


class TestFileManagerUtilsToTest: public QObject
{

Q_OBJECT

public:
TestFileManagerUtilsToTest();
virtual ~TestFileManagerUtilsToTest();
  private slots:
    void    TestparseFileKeyValueToTest();
    void    TestcreateFileToTest();
};

TestFileManagerUtilsToTest::TestFileManagerUtilsToTest()
{
}

TestFileManagerUtilsToTest::~TestFileManagerUtilsToTest()
{
}

void	TestFileManagerUtilsToTest::TestparseFileKeyValueToTest()
{
	std::string fileConf("sam.conf");
	std::vector<std::string> keyWords;
	keyWords.push_back("ip");
	keyWords.push_back("port");
    	FileManagerUtils *fileManager = new FileManagerUtils;

	std::map<std::string, std::string> ret = fileManager->parseFileKeyValue(fileConf, keyWords);
	std::cout << "ReturnValue : " + keyWords.at(0) << std::endl;
	QCOMPARE(keyWords.at(0), std::string("ip"));
	QCOMPARE(ret[keyWords.at(0)], std::string("192.168.1.2;"));
}

void	TestFileManagerUtilsToTest::TestcreateFileToTest()
{
	std::string 	filePath("test.conf");
	std::fstream 	*file;
	std::string	buffer;
	std::string data = "some data\n";

	file = FileManagerUtils::createFile(filePath);

	QCOMPARE(file->is_open(), true);

	if (file->is_open())
	{
            *file << data;
            file->seekg(0, std::fstream::beg);
            getline(*file, buffer);
	    QCOMPARE(buffer, std::string("some data"));
            file->close();
	}
}

QTEST_MAIN(TestFileManagerUtilsToTest)
#include "TestFileManagerUtilsToTest.moc"

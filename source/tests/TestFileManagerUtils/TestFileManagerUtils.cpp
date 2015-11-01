#include <QtTest/QtTest>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "TestFileManagerUtils.hpp"

TestFileManagerUtils::TestFileManagerUtils()
{
}

TestFileManagerUtils::~TestFileManagerUtils()
{
}

//
// Test function parseFileKeyValue
// Check if value from keyword are correct
//
void TestFileManagerUtils::TestParseFileKeyValue()
{
    std::string fileConf("sam.conf");
    std::vector<std::string> keyWords;
    keyWords.push_back("ip");
    keyWords.push_back("port");
    keyWords.push_back("other test");
    FileManagerUtils *fileManager = new FileManagerUtils;

    std::map<std::string, std::string> ret = fileManager->parseFileKeyValue(fileConf, keyWords);
    QCOMPARE(ret[keyWords.at(0)], std::string("192.168.1.2"));
    QCOMPARE(ret[keyWords.at(1)], std::string("789562"));
    QCOMPARE(ret[keyWords.at(2)], std::string("another test"));
}

//
// Test function createFile
// Check if the file is well create
//
void TestFileManagerUtils::TestCreateFile()
{
    std::string filePath("QtTestCreationFile.txt");
    std::fstream *file;

    file = FileManagerUtils::createFile(filePath);
    QCOMPARE(file->is_open(), true);
    file->close();
}

QTEST_MAIN(TestFileManagerUtils)

#ifndef TEST_FILE_MANAGER_UTILS_HPP_
# define TEST_FILE_MANAGER_UTILS_HPP_

# include <QtTest/QtTest>
# include <string>
# include <iostream>
# include <fstream>
# include <map>
# include "FileManagerUtils.hpp"

class TestFileManagerUtils : public QObject
{
    Q_OBJECT

public:
    TestFileManagerUtils();
    virtual ~TestFileManagerUtils();

private slots:
    void TestParseFileKeyValue();
    void TestCreateFile();
};

#endif // !TEST_FILE_MANAGER_UTILS_HPP_


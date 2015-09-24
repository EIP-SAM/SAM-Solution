#include <string>
#include <iostream>
#include <fstream>
#include "FileManagerUtils.hpp"

//
// This function parses a file to get keywords' values.
//

std::vector<std::string>	FileManagerUtils::parseFileKeyValue(const std::string &fileConf,
									std::vector<std::string> keywords)
{
    std::vector<std::string>	valueKeywords;
    std::string 		buffer;
    std::ifstream 		file(fileConf.c_str());
    bool 			findWord;

    if (!file) {
        std::cerr << "Error can not open file " << fileConf << std::endl;
        return valueKeywords;
    }
    file.seekg(0, std::ios::beg);
    while (getline(file, buffer, ':')) {
        findWord = false;

        for (int i = 0; i < keywords.size() && !findWord; ++i) {
            if (buffer.compare(keywords[i]) == 0) {
                getline(file, buffer);
                buffer.erase(0, 1);
                valueKeywords.push_back(buffer);
                findWord = true;
            }
        }
        if (!findWord)
            getline(file, buffer);
    }
    file.close();
    return valueKeywords;
}

#ifndef FILE_MANAGER_UTILS_HPP_
# define FILE_MANAGER_UTILS_HPP_


#include 					<vector>

class						FileManagerUtils
{
public:
    static std::map<std::string, std::string>	parseFileKeyValue(const std::string &fileConf,
								std::vector<std::string> keyWords);
    static std::fstream 			*createFile(const std::string);
};
#endif  /* !FILE_MANAGER_UTILS_HPP_ */



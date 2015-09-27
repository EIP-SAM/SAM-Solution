#ifndef FILE_MANAGER_UTILS_HPP_
# define FILE_MANAGER_UTILS_HPP_


#include 				<vector>

class					FileManagerUtils
{
public:
    static std::vector<std::string>	parseFileKeyValue(const std::string &fileConf,
								std::vector<std::string> keywords);
    static std::fstream 		*createFile(const std::string);
};
#endif  /* !FILE_MANAGER_UTILS_HPP_ */



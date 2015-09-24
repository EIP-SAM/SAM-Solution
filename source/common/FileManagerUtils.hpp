#ifndef FILE_MANAGER_UTILS_HPP_
# define FILE_MANAGER_UTILS_HPP_


#include 				<vector>

class					FileManagerUtils
{
public:
    static std::vector<std::string>	parseFileKeyValue(const std::string &fileConf,
								std::vector<std::string> keywords);
};
#endif  /* !FILE_MANAGER_UTILS_HPP_ */



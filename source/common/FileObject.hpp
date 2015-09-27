#ifndef FILE_OBJECT_HPP_
# define FILE_OBJECT_HPP_


#include 	<vector>

class		FileObject
{
private:
    int 	port;
    std::string ip;
    std::string nameFile;

public:
    FileObject(const std::string nameFile);

    int 	getPort(void);
    std::string getIp(void);
    std::string getNameFile(void);

    void setPort(int port);
    void setIp(std::string ip);
    void setNameFile(std::string nameFile);
};

#endif  /* !FILE_OBJECT_HPP */



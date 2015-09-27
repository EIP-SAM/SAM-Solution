#include <string>
#include <iostream>
#include <fstream>
#include "FileObject.hpp"

FileObject::FileObject(std::string nameFile)
{
    this->nameFile = nameFile;
}

void FileObject::setPort(int port)
{
    this->port = port;
}

void FileObject::setIp(std::string ip)
{
    this->ip = ip;
}

void FileObject::setNameFile(std::string nameFile)
{
    this->nameFile = nameFile;
}

int FileObject::getPort()
{
    return port;
}

std::string FileObject::getIp()
{
    return ip;
}

std::string FileObject::getNameFile()
{
    return nameFile;
}

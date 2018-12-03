//
// Created by Lucas on 03-Dec-18.
//

#include <utility>
#include <fstream>
#include <iostream>
#include <FileParser.hh>

FileParser::FileParser(std::string str)
{
    openFile(str);
}

bool FileParser::openFile(const std::string &file)
{
    std::cout << "Trying to open " << file << std::endl;

    // Close currenlty opened file
    closeFile();

    ifstream.open(file);
    if (ifstream.is_open())
        {
            fileName = file;
            return true;
        }
    else
        {
            std::cerr << "Error, cannot open file : " << file << std::endl;
            return false;
        }
}

FileParser::~FileParser()
{
    closeFile();
}

void FileParser::closeFile()
{
    if (ifstream.is_open())
        {
            ifstream.close();
        }
}

std::string FileParser::getLine()
{
    if (!ifstream.is_open())
        {
            std::cout << "Please open a file before reading." << std::endl;
            return "";
        }

    if (!ifstream.eof())
        {
            std::string line;
            std::getline(ifstream, line);
            return line;
        }
    else
        {
            std::cout << "You arrived at the end of the file." << std::endl;
            return "";
        }
}

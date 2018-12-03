//
// Created by Lucas on 03-Dec-18.
//

#ifndef KOREANVOCTESTER_FILEPARSER_HH
#define KOREANVOCTESTER_FILEPARSER_HH

#include <string>
#include <fstream>

class FileParser
{
public:
    explicit FileParser(std::string str);
    FileParser(const FileParser &) = delete;
    FileParser &operator=(const FileParser &) = delete;
    ~FileParser();

    bool    openFile(const std::string &str);
    void    closeFile();
    std::string getLine();

private:
    std::string fileName;
    std::ifstream ifstream;
};

#endif //KOREANVOCTESTER_FILEPARSER_HH

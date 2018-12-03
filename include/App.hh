//
// Created by Lucas on 03-Dec-18.
//

#ifndef KOREANVOCTESTER_APP_HH
#define KOREANVOCTESTER_APP_HH

#include <string>
#include <vector>
#include "FileParser.hh"

class App
{
public:
    App();
    ~App() = default;

    void start(int nbOfQuestions);

private:
    /* Consts */
    const std::string DictionaryName = "./data/Words.txt";
    const std::string QuestionDelimiter = "|";

    /* Attributes */
    FileParser fp;

    std::vector<std::string> questions;

    /* Functions */
    void    askQuestion(std::string question, int questionNumber);
    void    checkAnswer(std::string answer, std::string input);
    void    getData();

    std::pair<std::string, std::string>    parseQuestion(std::string question);
};


#endif //KOREANVOCTESTER_APP_HH

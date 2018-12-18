//
// Created by Lucas on 03-Dec-18.
//

#ifndef KOREANVOCTESTER_APP_HH
#define KOREANVOCTESTER_APP_HH

#include <string>
#include <vector>
#include "FileParser.hh"
#include "Window.hh"

class App
{
public:
    App();
    ~App() = default;

    void start(int nbOfQuestions);

    std::pair<std::string, std::string>    askQuestion();
    void    loadQuestions();
    bool    questionsLeft();
    void    clearQuestions();
    bool    checkAnswer(std::string answer) const;

    std::string getCurrentQuestion() const;
    std::string getCurrentAnswer() const;
    void setInputedAnswer(std::string answer);
    std::string getInputedAnswer() const;

private:
    /* Consts */
    const std::string DictionaryName = "./data/Words.txt";
    const std::string QuestionDelimiter = "|";

    /* Attributes */
    FileParser  _fp;
    Window  _win;

    std::vector<std::string> _questions;
    std::vector<std::string> _copyQuestions;
    std::pair<std::string, std::string> _currentQuestion;
    std::string _inputedAnswer;

    /* Functions */
    std::pair<std::string, std::string> askQuestion(std::string question);
    std::pair<std::string, std::string>    parseQuestion(std::string question);
    void    checkAnswer(std::string answer, std::string input);
    void    getData();
    void    copyQuestions();


};


#endif //KOREANVOCTESTER_APP_HH

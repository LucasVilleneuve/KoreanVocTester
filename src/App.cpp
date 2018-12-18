#include <utility>

//
// Created by Lucas on 03-Dec-18.
//

#include <iostream>
#include <utility>
#include <ctime>
#include <App.hh>
#include <StringOps.hpp>
#include "MainMenu.hh"
#include "QuestionScreen.hh"
#include "AnswerScreen.hh"

App::App()
 : _fp(DictionaryName), _win(800, 600)
{
    std::srand(std::time(nullptr));
    this->getData();
    _win.addScreen(new MainMenu(_win, *this));
    _win.addScreen(new QuestionScreen(_win, *this));
    _win.addScreen(new AnswerScreen(_win, *this));
}

void App::start(int nbOfQuestions)
{
    _win.startTimer();
    while (!_win.isWindowClosed())
        {
            _win.getEvent();

            _win.doStuff();

            _win.clear();
            _win.draw();
        }
//    int i = 0;
//
//    auto copyQuestions = questions;
//    while (i < nbOfQuestions && !copyQuestions.empty())
//        {
//            int nb = static_cast<int>(std::rand() % copyQuestions.size());
//            askQuestion(copyQuestions[nb], i + 1);
//            copyQuestions.erase(copyQuestions.begin() + nb);
//            ++i;
//        }
}

std::pair<std::string, std::string> App::askQuestion(std::string question)
{
    // Get word and answer
    auto pair = parseQuestion(std::move(question));
    if (pair.first.empty()) // Error
        {
            return std::make_pair("", "");
        }

    std::cout << "Translate \'" << pair.first << "\'." << std::endl;

    return pair;
}

void App::checkAnswer(std::string answer, std::string input)
{
    bool result = (answer == input);

    if (result)
        {
            std::cout << "Correct !" << std::endl;
        }
    else
        {
            std::cout << "Incorrect ! The answer was : \'" << answer << "\'." << std::endl;
        }
}

// TODO Maybe parse at beginning and only store correct questions
std::pair<std::string, std::string>  App::parseQuestion(std::string question)
{
    std::pair<std::string, std::string> pair;

    question = trim(question);

    size_t pos = 0;
    if ((pos = question.find(QuestionDelimiter)) != std::string::npos)
    {
        std::string word = question.substr(0, pos);
        question.erase(0, pos + QuestionDelimiter.length());
        return std::make_pair(trim(word), trim(question));
    }
    std::cerr << "Error, Question format is incorrect : cannot find delimiter." << std::endl;
    return std::make_pair("", "");
}

void App::getData()
{
    std::string question = _fp.getLine();
    while (!question.empty())
        {
            _questions.push_back(question);
            _copyQuestions.push_back(question);
            question = _fp.getLine();
        }
}

void    App::loadQuestions()
{
    clearQuestions();
    copyQuestions();
}

void App::copyQuestions()
{
    std::copy(_questions.begin(), _questions.end(), back_inserter(_copyQuestions));
}

bool App::questionsLeft()
{
    return !_copyQuestions.empty();
}

void App::clearQuestions()
{
    _copyQuestions.clear();
}

std::pair<std::string, std::string> App::askQuestion()
{
    if (questionsLeft())
        {
            int nb = static_cast<int>(std::rand() % _copyQuestions.size());
            auto pair = askQuestion(_copyQuestions[nb]);
            _copyQuestions.erase(_copyQuestions.begin() + nb);
            _currentQuestion = pair;
            return pair; // first is question, second is answer
        }
    else
        {
            std::cout << "No more questions to ask." << std::endl;
            // TODO Throw error or something ?
            auto pair = std::make_pair("", "");
            _currentQuestion = pair;
            return pair;
        }
}

std::string App::getCurrentQuestion() const
{
    return _currentQuestion.first;
}

std::string App::getCurrentAnswer() const
{
    return _currentQuestion.second;
}

bool App::checkAnswer(std::string answer) const
{
    return answer == _currentQuestion.second;
}

void App::setInputedAnswer(std::string answer)
{
    _inputedAnswer = std::move(answer);
}

std::string App::getInputedAnswer() const
{
    return _inputedAnswer;
}

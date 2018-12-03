#include <utility>

//
// Created by Lucas on 03-Dec-18.
//

#include <iostream>
#include <ctime>
#include <App.hh>
#include <StringOps.hpp>

App::App()
 : fp(DictionaryName)
{
    std::srand(std::time(nullptr));
    getData();
}

void App::start(int nbOfQuestions)
{
    int i = 0;

    auto copyQuestions = questions;
    while (i < nbOfQuestions && !copyQuestions.empty())
        {
            int nb = static_cast<int>(std::rand() % copyQuestions.size());
            askQuestion(copyQuestions[nb], i + 1);
            copyQuestions.erase(copyQuestions.begin() + nb);
            ++i;
        }
}

void App::askQuestion(std::string question, int questionNumber)
{
    // Get word and answer
    auto pair = parseQuestion(std::move(question));
    if (pair.first.empty()) // Error
        {
            return;
        }

    std::cout << "Question number " << questionNumber << ".\n";
    std::cout << "Translate \'" << pair.first << "\'." << std::endl;

    // Get user input
    std::string input;
    getline(std::cin, input);

    checkAnswer(pair.second, input);
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
            std::cout << "Inorrect ! The answer was : \'" << answer << "\'." << std::endl;
        }
}

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
    std::string question = fp.getLine();
    while (!question.empty())
        {
            questions.push_back(question);
            question = fp.getLine();
        }
}

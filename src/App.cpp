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

void App::start()
{
  _win.startTimer();
  while (!_win.isWindowClosed())
	{
	  _win.getEvent();

	  _win.doStuff();

	  _win.clear();
	  _win.draw();
	}

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

void    App::reset()
{
  clearQuestions();
  copyQuestions();
  _questionAsked = 0;
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
  std::pair<std::string, std::string> pair;

  if (!canAskQuestion())
	{
	  std::cout << "No more questions to ask." << std::endl;
	  // TODO Throw error or something ?
	  pair = std::make_pair("", "");
	  _currentQuestion = pair;
	}
  else
	{
	  ++_questionAsked;
	  int nb = static_cast<int>(std::rand() % _copyQuestions.size());
	  pair = askQuestion(_copyQuestions[nb]);
	  _copyQuestions.erase(_copyQuestions.begin() + nb);
	}

  _currentQuestion = pair;
  return pair; // first is question, second is answer
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

int App::getNumberOfQuestionsToAsk() const
{
  return _numberOfQuestionsToAsk;
}

void App::setNumberOfQuestionsToAsk(int nb)
{
  _numberOfQuestionsToAsk = nb;
}

bool App::canAskQuestion()
{
  if (!questionsLeft()) return false;
  if (_numberOfQuestionsToAsk == -1) return true; // If == -1, then ask all the questions
  return (_questionAsked < _numberOfQuestionsToAsk);
}

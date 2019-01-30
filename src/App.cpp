//
// Created by Lucas on 03-Dec-18.
//

#include <iostream>
#include <utility>
#include <ctime>
#include "App.hh"
#include "StringOps.hpp"
#include "MainMenu.hh"
#include "QuestionScreen.hh"
#include "AnswerScreen.hh"

App::App()
		: _db(DatabaseName), _win(800, 600)
{
  std::srand(std::time(nullptr));
  this->getData();
  this->copyQuestions();
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

void App::getData()
{
  auto result = _db.execute("SELECT * FROM Words");

  for (const auto &queryContent : result)
	{
	  std::string word;
	  std::string translation;
	  int type = 0;

	  for (int i = 0; i < queryContent.nbCol; ++i)
		{
		  if (queryContent.colNames[i] == "word")
			{
			  word = queryContent.content[i];
			}
		  else if (queryContent.colNames[i] == "translation")
			{
			  translation = queryContent.content[i];
			}
		  else if (queryContent.colNames[i] == "type")
			{
			  type = std::stoi(queryContent.content[i]);
			}
		}

	  _questions.emplace_back(word, translation, static_cast<WordType>(type));
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

Word App::askQuestion()
{
  Word w ("", "", WordType::UNKNOWN);

  if (canAskQuestion())
	{
	  ++_questionAsked;
	  auto nb = static_cast<int>(std::rand() % _copyQuestions.size());
	  w = _copyQuestions[nb];
	  _copyQuestions.erase(_copyQuestions.begin() + nb);
	}
  else
	{
	  std::cout << "No more questions to ask." << std::endl;
	  // TODO Throw error or something ?
	}

	std::cout << "Current question is : " << w.word << std::endl;
  _currentQuestion = w;
  return w;
}

Word App::getCurrentQuestion() const
{
  return _currentQuestion;
}

std::string App::getCurrentAnswer() const
{
  return _currentQuestion.translation;
}

bool App::checkAnswer(std::string answer) const
{
  std::string modifiedAnswer = toLower(removeSpaces(answer));
  std::string copyCorrectAnswer = _currentQuestion.translation;
  toLower(removeSpaces(copyCorrectAnswer));

  return areStringsRoughlyEquivalent(modifiedAnswer, copyCorrectAnswer, 1);
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

bool App::areStringsRoughlyEquivalent(std::string in, std::string an, unsigned int nbErrorsMax)
{
  unsigned int lenStr1 = in.length();
  unsigned int lenStr2 = an.length();
  unsigned int nbErrors = 0;

  if (lenStr1 == lenStr2) // Same size
	{
	  for (unsigned int i = 0; i < lenStr1; ++i)
		{
		  if (in[i] != an[i])
			++nbErrors;
		}
	}
  else if (lenStr1 > lenStr2) // Input bigger
	{
	  nbErrors = countNbErrors(in, an);
	}
  else // Input smaller
	{
	  nbErrors = countNbErrors(an, in);
	}
  return nbErrors <= nbErrorsMax;
}

unsigned int App::countNbErrors(std::string str1, std::string str2)
{
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int nbErrors = 0;

  while (i < str1.length())
	{
	  if (j < str2.length() && str1[i] == str2[j])
		{
		  ++j;
		}
	  else
		{
		  ++nbErrors;
		}
	  ++i;
	}
  return nbErrors;
}

std::string App::getCurrentWord() const
{
  return _currentQuestion.word;
}

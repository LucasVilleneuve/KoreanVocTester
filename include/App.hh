//
// Created by Lucas on 03-Dec-18.
//

#ifndef KOREANVOCTESTER_APP_HH
#define KOREANVOCTESTER_APP_HH

#include <string>
#include <vector>
#include "Window.hh"
#include "DatabaseHandler.hh"
#include "Word.hpp"

class App
{
public:
	App();
	~App() = default;

	void	start();
	void    reset();
	bool	canAskQuestion();
	void    clearQuestions();
	bool    checkAnswer(std::string answer) const;
	Word    askQuestion();

	/* Getters and setters */
	Word		getCurrentQuestion() const;
	std::string getCurrentWord() const;
	std::string	getCurrentAnswer() const;
	std::string	getInputedAnswer() const;
	void		setInputedAnswer(std::string answer);
	int 		getNumberOfQuestionsToAsk() const;
	void 		setNumberOfQuestionsToAsk(int nb);

private:
	/* Consts */
	const std::string DatabaseName = "../data/Words.sqlite";

	/* Attributes */
	DatabaseHandler _db;
	Window 			_win;

	std::vector<Word>	_questions;
	std::vector<Word>	_copyQuestions;
	Word				_currentQuestion;
	std::string			_inputedAnswer;
	int					_numberOfQuestionsToAsk = 0;
	int					_questionAsked = 0;

	/* Functions */
	void    getData();
	void    copyQuestions();
	bool    questionsLeft();
	static bool	areStringsRoughlyEquivalent(std::string str1, std::string str2, unsigned int nbErrorsMax);
	static unsigned int countNbErrors(std::string str1, std::string str2);
};

#endif //KOREANVOCTESTER_APP_HH
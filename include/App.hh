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

	void	start();
	void    reset();
	bool	canAskQuestion();
	void    clearQuestions();
	bool    checkAnswer(std::string answer) const;
	std::pair<std::string, std::string>    askQuestion();

	/* Getters and setters */
	std::string	getCurrentQuestion() const;
	std::string	getCurrentAnswer() const;
	void	setInputedAnswer(std::string answer);
	std::string	getInputedAnswer() const;
	int getNumberOfQuestionsToAsk() const;
	void setNumberOfQuestionsToAsk(int nb);

private:
	/* Consts */
	const std::string DictionaryName = "../data/Words.txt";
	const std::string QuestionDelimiter = "|";

	/* Attributes */
	FileParser 	_fp;
	Window 		_win;

	std::vector<std::string>	_questions;
	std::vector<std::string>	_copyQuestions;
	std::pair<std::string, std::string>	_currentQuestion;
	std::string	_inputedAnswer;
	int	_numberOfQuestionsToAsk = 0;
	int _questionAsked = 0;

	/* Functions */
	std::pair<std::string, std::string>	askQuestion(std::string question);
	std::pair<std::string, std::string>    parseQuestion(std::string question);
	void    getData();
	void    copyQuestions();
	bool    questionsLeft();
	static bool	areStringsRoughlyEquivalent(std::string str1, std::string str2, unsigned int nbErrorsMax);
	static unsigned int countNbErrors(std::string str1, std::string str2);
};

#endif //KOREANVOCTESTER_APP_HH
//
// Created by Lucas on 13-Dec-18.
//

#ifndef KOREANVOCTESTER_QUESTIONSCREEN_HH
#define KOREANVOCTESTER_QUESTIONSCREEN_HH

#include "Screen.hh"

class App;

class QuestionScreen : public Screen
{
public:
	QuestionScreen(Window &win, App &a);
	~QuestionScreen();

	void doStuff() override;

private:
	/* Attributes */
	App                 &app;
	std::string         currentQuestion;
	char                input[256] {};

	/* Functions */
	void clearInput();
};


#endif //KOREANVOCTESTER_QUESTIONSCREEN_HH

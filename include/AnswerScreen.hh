//
// Created by Lucas on 13-Dec-18.
//

#ifndef KOREANVOCTESTER_ANSWERSCREEN_HH
#define KOREANVOCTESTER_ANSWERSCREEN_HH

#include "Screen.hh"

class App;

class AnswerScreen : public Screen
{
public:
    AnswerScreen(Window &win, const std::string &screenName, App &a);
    ~AnswerScreen();

    void doStuff() override;

private:
    App                 &app;

    std::string         answer;
};


#endif //KOREANVOCTESTER_ANSWERSCREEN_HH

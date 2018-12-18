//
// Created by Lucas on 18-Dec-18.
//

#ifndef KOREANVOCTESTER_MAINMENU_HH
#define KOREANVOCTESTER_MAINMENU_HH

#include "Screen.hh"

class App;

class MainMenu : public Screen
{
public:
    MainMenu(Window &win, App &a);
    ~MainMenu();

    void doStuff() override;

private:
    App &app;
};


#endif //KOREANVOCTESTER_MAINMENU_HH

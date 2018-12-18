//
// Created by Lucas on 18-Dec-18.
//

#include "App.hh"
#include "MainMenu.hh"


MainMenu::MainMenu(Window &win, App &a)
 : Screen(win), app(a)
{
}

MainMenu::~MainMenu() = default;

void MainMenu::doStuff()
{
    if (nk_begin(ctx, "MainMenu Screen", nk_rect(0, 0, window.getWidth() , window.getHeight()), 0))
        {
            nk_layout_row_dynamic(ctx, 300, 1);
            {
                nk_label(ctx, std::string("Korean Vocabulary Tester").c_str(), NK_TEXT_CENTERED);
            }

            nk_layout_row_dynamic(ctx, 100, 1);
            {
                if (nk_button_label(ctx, "Start"))
                    {
                        app.loadQuestions();
                        app.askQuestion();
                        window.incrementScreenIndex();
                    }
            }
        }
    nk_end(ctx);
}
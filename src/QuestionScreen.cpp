//
// Created by Lucas on 13-Dec-18.
//

#include <iostream>
#include <cstring>
#include <QuestionScreen.hh>

#include "QuestionScreen.hh"
#include "App.hh"

QuestionScreen::QuestionScreen(Window &win, App &a)
 : Screen(win), app(a)
{
}

QuestionScreen::~QuestionScreen() = default;

void QuestionScreen::doStuff()
{
    currentQuestion.assign(app.getCurrentQuestion());
    if (nk_begin(ctx, "Question Screen", nk_rect(0, 0, window.getWidth() , window.getHeight()), 0))
        {
            nk_layout_row_dynamic(ctx, 300, 1);
            {
                nk_label(ctx, std::string("Translate : " + currentQuestion).c_str(), NK_TEXT_CENTERED);
            }

            nk_layout_row_static(ctx, 100, 380, 2);
            {
                nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD|NK_EDIT_AUTO_SELECT, input, sizeof(input), nk_filter_ascii);
                if (nk_button_label(ctx, "Check answer"))
                    {
                        app.setInputedAnswer(input);
                        clearInput();
                        window.incrementScreenIndex();
                    }
            }
        }
    nk_end(ctx);
}

void QuestionScreen::clearInput()
{
    std::strcpy(input, "");
}

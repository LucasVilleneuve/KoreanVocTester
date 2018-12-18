//
// Created by Lucas on 13-Dec-18.
//

#include <string>
#include <App.hh>
#include "AnswerScreen.hh"

AnswerScreen::AnswerScreen(Window &win, App &a)
 : Screen(win), app(a)
{
}

AnswerScreen::~AnswerScreen() = default;

void AnswerScreen::doStuff()
{
    answer = app.getCurrentAnswer();

    if (nk_begin(ctx, "Answer screen", nk_rect(0, 0, window.getWidth() , window.getHeight()), 0))
        {
            nk_layout_row_dynamic(ctx, 150, 1);
            {
                bool result = app.checkAnswer(app.getInputedAnswer());
                nk_label(ctx, result ? "Correct!" : "Incorrect", NK_TEXT_CENTERED);
            }
            nk_layout_row_dynamic(ctx, 150, 1);
            {
                nk_label(ctx, std::string("The answer was : " + answer).c_str(), NK_TEXT_CENTERED);
            }
            nk_layout_row_static(ctx, 100, 400, 1);
            {
                if (nk_button_label(ctx, "Next question"))
                    {
                        if (app.questionsLeft())
                            {
                                window.decrementScreenIndex();
                                app.askQuestion();
                            }
                            else
                            {
                                window.decrementScreenIndex();
                                window.decrementScreenIndex();
                            }
                    }
            }
        }
    nk_end(ctx);
}

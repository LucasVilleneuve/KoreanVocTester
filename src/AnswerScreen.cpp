//
// Created by Lucas on 13-Dec-18.
//

#include <string>
#include <App.hh>
#include "AnswerScreen.hh"

AnswerScreen::AnswerScreen(Window &win, const std::string &screenName, App &a)
		: Screen(win, screenName), app(a)
{
}

AnswerScreen::~AnswerScreen() = default;

void AnswerScreen::doStuff()
{
  answer = app.getCurrentAnswer();

  if (nk_begin(ctx, "Answer screen", nk_rect(0, 0, _window.getWidth() , _window.getHeight()), 0))
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

	  nk_layout_row_begin(ctx, NK_DYNAMIC, 100, 2);
	  nk_layout_row_push(ctx, 0.25);
	  nk_spacing(ctx, 1);
	  nk_layout_row_push(ctx, 0.5);
	  if (nk_button_label(ctx, "Next question"))
		{
		  if (app.canAskQuestion())
			{
			  _window.changeScreen("Question");
			  app.askQuestion();
			}
		  else
			{
			  _window.changeScreen("MainMenu");
			}
		}
	  nk_layout_row_end(ctx);
	}
  nk_end(ctx);
}

//
// Created by Lucas on 18-Dec-18.
//

#include "App.hh"
#include "MainMenu.hh"

MainMenu::MainMenu(Window &win, const std::string &screenName, App &a)
		: Screen(win, screenName), app(a)
{
}

MainMenu::~MainMenu() = default;

void MainMenu::doStuff()
{
  if (nk_begin(ctx, "MainMenu Screen", nk_rect(0, 0, _window.getWidth() , _window.getHeight()), 0))
	{
	  nk_layout_row_dynamic(ctx, 300, 1);
	  {
		nk_label(ctx, std::string("Korean Vocabulary Tester").c_str(), NK_TEXT_CENTERED);
	  }

	  nk_layout_row_begin(ctx, NK_DYNAMIC, 100, 6);
	  nk_layout_row_push(ctx, 0.0625);
	  nk_spacing(ctx, 1);
	  nk_layout_row_push(ctx, 0.25);
	  if (nk_button_label(ctx, "5"))
		{
		  app.reset();
		  app.setNumberOfQuestionsToAsk(5);
		  app.askQuestion();
		  _window.changeScreen("Question");
		}
	  nk_layout_row_push(ctx, 0.0625);
	  nk_spacing(ctx, 1);
	  nk_layout_row_push(ctx, 0.25);
	  if (nk_button_label(ctx, "10"))
		{
		  app.reset();
		  app.setNumberOfQuestionsToAsk(10);
		  app.askQuestion();
		  _window.changeScreen("Question");

		}
	  nk_layout_row_push(ctx, 0.0625);
	  nk_spacing(ctx, 1);
	  nk_layout_row_push(ctx, 0.25);
	  if (nk_button_label(ctx, "All"))
		{
		  app.reset();
		  app.setNumberOfQuestionsToAsk(-1);
		  app.askQuestion();
		  _window.changeScreen("Question");
		}
	  nk_layout_row_end(ctx);


		// TODO Quit button
	}
  nk_end(ctx);
}
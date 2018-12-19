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

	  nk_layout_row_dynamic(ctx, 100, 3);
	  {
		if (nk_button_label(ctx, "Fast (5)"))
		  {
			app.reset();
			app.setNumberOfQuestionsToAsk(5);
			app.askQuestion();
			window.incrementScreenIndex();
		  }
		if (nk_button_label(ctx, "Normal (10)"))
		  {
			app.reset();
			app.setNumberOfQuestionsToAsk(10);
			app.askQuestion();
			window.incrementScreenIndex();
		  }
		if (nk_button_label(ctx, "All"))
		  {
			app.reset();
			app.setNumberOfQuestionsToAsk(-1);
			app.askQuestion();
			window.incrementScreenIndex();
		  }
	  }
	}
  nk_end(ctx);
}
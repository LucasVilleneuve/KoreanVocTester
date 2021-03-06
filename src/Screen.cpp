//
// Created by Lucas on 05-Dec-18.
//

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#define NK_ALLEGRO5_IMPLEMENTATION

#include <iostream>
#include "Screen.hh"
#include "Window.hh"

Screen::Screen(Window &win, const std::string &screenName)
		: _window(win), _name(screenName)
{
  init();
}

Screen::~Screen()
{
  nk_allegro5_font_del(font);
  nk_allegro5_shutdown();
}

void Screen::init()
{
  font = nk_allegro5_font_create_from_file(FONT, FONT_SIZE, 0); // TODO Change font
  ctx = nk_allegro5_init(font, _window.getDisplay(), _window.getWidth(), _window.getHeight());
}

void Screen::render()
{
  nk_allegro5_render();
}

void Screen::handleEvent(ALLEGRO_EVENT *ev)
{
  nk_input_begin(ctx);
  nk_allegro5_handle_event(ev);
  if (nk_input_is_key_down(&ctx->input, NK_KEY_ENTER))
	{
	  std::cout << "Enter is pressed" << std::endl;
	  // TODO Do domething here
	}
  nk_input_end(ctx);
}

void Screen::clear()
{
  nk_clear(ctx);
}

std::string Screen::getName() const
{
  return _name;
}

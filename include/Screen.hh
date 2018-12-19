//
// Created by Lucas on 05-Dec-18.
//

#ifndef KOREANVOCTESTER_SCREEN_HH
#define KOREANVOCTESTER_SCREEN_HH

#include <allegro5/events.h>
#include "nuklear.h"
#include "nuklear_allegro5.h"

class Window;
struct NkAllegro5Font;
struct nk_context;

class Screen
{
public:
	explicit Screen(Window &win);
	~Screen();

	virtual void    init();
	virtual void    render();
	virtual void    handleEvent(ALLEGRO_EVENT *ev);
	virtual void    doStuff() = 0;
	void    clear();

protected:
	Window              &window;
	NkAllegro5Font      *font = nullptr;
	struct nk_context   *ctx = nullptr;

	const int           FONT_SIZE = 42;
};


#endif //KOREANVOCTESTER_SCREEN_HH

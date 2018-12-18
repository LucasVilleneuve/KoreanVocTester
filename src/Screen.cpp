//
// Created by Lucas on 05-Dec-18.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#define NK_ALLEGRO5_IMPLEMENTATION

#include "Screen.hh"
#include "Window.hh"


Screen::Screen(Window &win)
 : window(win)
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
    font = nk_allegro5_font_create_from_file("./fonts/Typo_DodamM.ttf", FONT_SIZE, 0); // TODO Change font
    ctx = nk_allegro5_init(font, window.getDisplay(), window.getWidth(), window.getHeight());
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
//
// Created by Lucas on 05-Dec-18.
//

#include <iostream>
#include <Window.hh>
#include "Screen.hh"

Window::Window(unsigned int w, unsigned int h)
{
  init();
  createDisplay(w, h);

  // Register events
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_mouse_event_source());
}

Window::~Window()
{
  destroyDisplay();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
}

void Window::init()
{
  al_init(); // TODO Can fail
  al_install_keyboard(); // TODO Can fail
  al_install_mouse(); // TODO Can fail
  al_set_mouse_wheel_precision(150);

  timer = al_create_timer(1.0 / FRAMES_PER_SECOND); // TODO Can fail
  queue = al_create_event_queue(); // TODO Can fail
}

void Window::createDisplay(unsigned int w, unsigned int h)
{
  width = w;
  height = h;
  display = al_create_display(w, h);

  if (!display)
	{
	  std::cerr << "Error, Cannot create display." << std::endl;
	  return; // TODO Throw exception ?
	}
}

void Window::destroyDisplay()
{
  if (display)
	{
	  al_destroy_display(display);
	  display = nullptr;
	}
}

unsigned int Window::getWidth() const
{
  return width;
}

unsigned int Window::getHeight() const
{
  return height;
}

void Window::draw()
{
  (*currentIndex)->render();

  if (redraw)
	{
	  al_flip_display();
	  redraw = false;
	}
}

void Window::clear()
{
  al_clear_to_color(al_map_rgb(0, 0, 0)); // Clear screen
}

ALLEGRO_EVENT Window::getEvent()
{
  al_wait_for_event(queue, &event);

  if (event.type == ALLEGRO_EVENT_TIMER)
	{
	  redraw = true;
	}

  (*currentIndex)->handleEvent(&event);

  return event;
}

bool    Window::isWindowClosed()
{
  return (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE);
}

void Window::startTimer()
{
  al_start_timer(timer);
}

ALLEGRO_DISPLAY *Window::getDisplay() const
{
  return display;
}

void Window::doStuff()
{
  (*currentIndex)->doStuff();
}

void Window::addScreen(Screen *scr)
{
  bool needToInit = screens.empty();

  screens.push_back(std::unique_ptr<Screen>(scr));

  if (needToInit)
	  currentScreen = scr->getName();
  changeScreen(currentScreen);
}

void Window::changeScreen(const std::string &name)
{
  for (auto it = screens.begin(); it != screens.end(); ++it)
	{
	  if ((*it)->getName() == name)
		{
		  currentIndex = it;
		  currentScreen = name;
		  return;
		}
	}
  std::cerr << "Cannot find screen named \"" << name << "\"." << std::endl;
}

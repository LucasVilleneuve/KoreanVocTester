//
// Created by Lucas on 05-Dec-18.
//

#ifndef KOREANVOCTESTER_WINDOW_HH
#define KOREANVOCTESTER_WINDOW_HH

#include <allegro5/allegro.h>
#include <memory>
#include <vector>

// TODO Gestion d'erreur

class Screen;

class Window
{
public:
    Window(unsigned int w, unsigned int h);
    ~Window();

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    ALLEGRO_DISPLAY *getDisplay() const;

    void draw();
    void clear();
    ALLEGRO_EVENT getEvent();
    bool    isWindowClosed();
    void    startTimer();
    void    doStuff();
    void    addScreen(Screen *scr);

    // Screen index
    void    incrementScreenIndex();
    void    decrementScreenIndex();

private:
    void init();
    void createDisplay(unsigned int w, unsigned int h);
    void destroyDisplay();

    const float FRAMES_PER_SECOND = 60.0f;

    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_TIMER   *timer = nullptr;
    ALLEGRO_EVENT_QUEUE *queue = nullptr;
    ALLEGRO_EVENT event;
    unsigned int width;
    unsigned int height;
    bool redraw = true;

    std::vector<std::unique_ptr<Screen>> screens;
    unsigned int currentScreenIndex = 0;
};


#endif //KOREANVOCTESTER_WINDOW_HH

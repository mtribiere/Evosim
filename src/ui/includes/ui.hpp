#ifndef _UI_H_
#define _UI_H_
#include "SDL.h"

#define WINDOW_HEIGHT 400
#define WINDOW_WIDTH 300

class UI {      
    public:          
        UI();
        int initDisplay();

        void UpdateDisplay();
        void ClearDisplay();
        void drawRectangle(int x, int y, int w, int h, int r, int g, int b);

        void sleep(Uint32 ms);

        void pullLastEvent();
        bool shouldQuit();

        ~UI();

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Surface *surface;
        SDL_Event event;
     
};

#endif
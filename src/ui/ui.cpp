#include "ui.hpp"

UI::UI()
{
}

int UI::initDisplay()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (SDL_CreateWindowAndRenderer(300, 400, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    return 0;
}

//        SDL_SetRenderDrawColor(this->renderer, 0xFF, 0x00, 0x00, 0x00);


void UI::UpdateDisplay()
{
    SDL_RenderPresent(this->renderer);
}

void UI::ClearDisplay()
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);
}

void UI::pullLastEvent()
{
    SDL_PollEvent(&(this->event));
}

bool UI::shouldQuit()
{
    return (event.type == SDL_QUIT);
}


void UI::drawRectangle(int x, int y, int w, int h, int r, int g, int b)
{
    
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(this->renderer, r, g, b, 255);
    SDL_RenderDrawRect(this->renderer, &rect);
    SDL_RenderFillRect(this->renderer, &rect);
}

void UI::sleep(Uint32 ms)
{
    SDL_Delay(ms);
}

UI::~UI()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    SDL_Quit();
}

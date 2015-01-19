//
// sdl2-imgrotate.cpp - Rotate an image on the screen
//
// Based on SDL2 tutorial:
//
//  * http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world/
//

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

#define IMAGE_FILENAME "sdl2-image.bmp"

int main(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Rotate Image", 0, 0, 0, 0, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::string imagePath = IMAGE_FILENAME;
    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
    if (bmp == nullptr){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);

    SDL_Event event;
    float frotate=0.0f;
    int delay=10; // milliseconds
    bool runrun=true;

    while (runrun) {

        SDL_RenderCopyEx(ren, tex, NULL, NULL, frotate, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderPresent(ren);
        SDL_Delay(delay);
        frotate += 0.5f;

        while (SDL_PollEvent (&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_Quit();
                    runrun=false;
                }
            }
        }
    }

    SDL_Quit();
    return 0;
}

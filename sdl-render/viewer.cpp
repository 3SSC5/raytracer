#include <iostream>
#include <SDL2/SDL.h>

constexpr int WIDTH = 256;
constexpr int HEIGHT = 256;


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL failed to initialise: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window  = SDL_CreateWindow(
        "Viewer",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT, 0);

    if (window == nullptr) {
        std::cerr << "Window failed: " << SDL_GetError << "\n";
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }


    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include <fstream>



int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cerr << "Could not open\n";
        return 1;
    }

    std::string magic;
    int width, height, maxval;

    file >> magic >> width >> height >> maxval;

    if (!file || magic != "P3" || width <= 0 || height <= 0 || maxval != 255)
    {
        std::cerr << "Wrong ppm or file type\n";
        return 1;
    }

    std::vector<Uint8> framebuffer(width * height * 3); 

    for (int i = 0; i < width * height; i++) {
        int r, g, b;
        file >> r >> g >> b;

        framebuffer[i * 3 + 0] = static_cast<Uint8>(r);
        framebuffer[i * 3 + 1] = static_cast<Uint8>(g);
        framebuffer[i * 3 + 2] = static_cast<Uint8>(b);
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL failed to initialise: " << SDL_GetError() << "\n";
        return 1;
    }

    if (!file) {
        std::cerr << "File ended early or has bad data\n";
        return 1;
    }

    SDL_Window* window  = SDL_CreateWindow(
        "Viewer",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, 0);

    if (window == nullptr) {
        std::cerr << "Window failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == nullptr) {
        std::cerr << "Renderer failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING, width, height);
    
    if (texture == nullptr) {
        std::cerr << "Texture failed: " <<  SDL_GetError() << "\n";
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    SDL_UpdateTexture(texture, nullptr, framebuffer.data(), width * 3);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
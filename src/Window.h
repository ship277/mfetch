#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <iostream>

class Window {
public:
    Window() {
        SDL_CreateWindowAndRenderer(
            "tutorial",
            800, 300,
            SDL_WINDOW_OPENGL,
            &window, &renderer
        );
    }

    void Render() {

    }

    void Update(SDL_Texture* texture, SDL_FRect shape) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (texture)
            SDL_RenderTexture(renderer, texture, nullptr, &shape);
        SDL_RenderPresent(renderer);
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    ~Window() {
        if (window && SDL_WasInit(SDL_INIT_VIDEO)) {
            SDL_DestroyWindow(window);
        } else {
            std::cout << "Skipping SDL_DestroyWindow\n";
        }
    }

    SDL_Window* GetWindow() {
        return window;
    }
    SDL_Renderer* GetRenderer() {
        return renderer;
    }

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

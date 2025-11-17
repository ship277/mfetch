#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <filesystem>
#include <vector>
#include <ctime>
#include <bits/stdc++.h>

namespace fs = std::filesystem;
using std::cout;
using std::endl;

bool init();
void kill();
bool action();
bool fetch();

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* texture = nullptr;
SDL_FRect shape;

fs::path msd = "/home/paul/Pictures/Mayushii☆"; // edit path to your picture folder
std::vector<fs::path> mayushiis;
int rng;
const float maxWw = 600, maxWh = 600; // you can set the maximum size the window will have; the longest side of the image will fit to that. aspect ratio preserved

class MTexture {
    public:
        float tw, th, scale;
};
MTexture currentTexture;

int main(int argc, char** argv) {
    srand(time(0));

    if (!init()) {
        cout << "Failed to initialize anything lmao: " << SDL_GetError() << endl;
        return 1;
    }
    
    if (!fs::exists(msd) || !fs::is_directory(msd)) {
        cout << "Directory not found: " << msd << endl;
        kill();
        return 1;
    }

    for (const auto& mayushii : fs::directory_iterator{msd})
        mayushiis.push_back(mayushii.path());

    if (mayushiis.empty()) {
    cout << "No images found in directory: " << msd << endl;
    kill();
    return 1;
    }

    fetch();

    while (action())
        SDL_Delay(10);

    kill();
    return 0;
}

bool fetch() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    rng = rand() % mayushiis.size();
    std::string tPath = mayushiis[rng]; // windows only: necessary to append ".u8string()"
    texture = IMG_LoadTexture(renderer, tPath.c_str());
    if (!texture) {
        cout << "Failed to load the texture: Check for unsupported format." << endl;
    }

    int ww, wh;
    float war, tar;
    SDL_GetWindowSize(window, &ww, &wh);
    SDL_GetTextureSize(texture, &currentTexture.tw, &currentTexture.th);
    war = maxWw / maxWh;
    tar = currentTexture.tw / currentTexture.th;

    if (war < tar)
        currentTexture.scale = maxWw / currentTexture.tw;
    else
        currentTexture.scale = maxWh / currentTexture.th;

    shape.w = currentTexture.tw * currentTexture.scale;
    shape.h = currentTexture.th * currentTexture.scale;
    SDL_SetWindowSize(window, (currentTexture.tw * currentTexture.scale), (currentTexture.th * currentTexture.scale));
    SDL_GetWindowSize(window, &ww, &wh);
    shape.x = (ww - shape.w)/2;
    shape.y = (wh - shape.h)/2;

    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, nullptr, &shape);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RenderPresent(renderer);

    // Live debugging info // oh how many times have you saved me <3
    // cout << shape.x << endl;
    // cout << shape.y << endl;
    // cout << shape.w << endl;
    // cout << shape.h << endl;
    // cout << ww << endl;
    // cout << wh << endl;
    // cout << endl;

    return true;
}

bool action() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_EVENT_QUIT:
                return false;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                fetch();
                break;
            default:
                break;
        }
    }
    return true;
}

// boring boilerplate stuff
bool init() {
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow(
            "Mayushii☆Fetch v.1.2.1 - Zen Deluxe Edition",
            maxWw, maxWh,
            SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS
            );
    SDL_SetWindowResizable(window, true);
    SDL_ShowWindow(window);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to create a renderer: %s", SDL_GetError());
        return false;
    }
    SDL_RenderClear(renderer);
    return true;
}

void kill() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
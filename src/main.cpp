#include <SDL3/SDL_mouse.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <filesystem>
#include <vector>
#include <ctime>
#include <bits/stdc++.h>
#include "Window.h"

namespace fs = std::filesystem;
using std::cout;
using std::endl;

struct ProgramState {
    Window window;
    Uint64 PreviousFrame = 0;
};

SDL_HitTestResult HitTestCallback(SDL_Window* win, const SDL_Point* area, void* data) {
    Window* window = static_cast<Window*>(data);
    return SDL_HITTEST_DRAGGABLE;
}

struct MTexture {
    float tw, th, scale;
};
MTexture currentTexture;

SDL_Texture* texture;
SDL_FRect shape;

fs::path p = fs::current_path()/"Mayushii☆";
std::vector<fs::path> mayushiis;
int rng;
const float maxWw = 600, maxWh = 600; // you can set the maximum size the window will have; the longest side of the image will fit to that. aspect ratio preserved

void fetch(void* AppState) {
    ProgramState* state = static_cast<ProgramState*>(AppState);

    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    rng = rand() % mayushiis.size();
    std::string tPath = mayushiis[rng].u8string();
    texture = IMG_LoadTexture(state->window.GetRenderer(), tPath.c_str());
    if (!texture) {
        cout << "Failed to load the texture: Check for unsupported format. Only static images are allowed" << endl;
    }

    int ww, wh;
    float war, tar;
    SDL_GetWindowSize(state->window.GetWindow(), &ww, &wh);
    SDL_GetTextureSize(texture, &currentTexture.tw, &currentTexture.th);
    war = maxWw / maxWh;
    tar = currentTexture.tw / currentTexture.th;

    if (war < tar)
        currentTexture.scale = maxWw / currentTexture.tw;
    else
        currentTexture.scale = maxWh / currentTexture.th;

    shape.w = currentTexture.tw * currentTexture.scale;
    shape.h = currentTexture.th * currentTexture.scale;
    SDL_SetWindowSize(state->window.GetWindow(), (currentTexture.tw * currentTexture.scale), (currentTexture.th * currentTexture.scale));
    SDL_GetWindowSize(state->window.GetWindow(), &ww, &wh);
    shape.x = (ww - shape.w)/2;
    shape.y = (wh - shape.h)/2;

    SDL_SetWindowPosition(state->window.GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

SDL_AppResult SDL_AppInit(void** AppState, int, char**) {
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);

    ProgramState* state = new ProgramState();
    state->PreviousFrame = SDL_GetTicks();
    *AppState = state;

    for (const auto& mayushii : fs::directory_iterator{p})
        mayushiis.push_back(mayushii.path());
    fetch(state);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* AppState, SDL_Event* e) {
    ProgramState* state = static_cast<ProgramState*>(AppState);

    if (e->type == SDL_EVENT_QUIT || e->key.key == SDLK_ESCAPE)
        return SDL_APP_SUCCESS;
    if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (e->button.button == SDL_BUTTON_RIGHT)
            fetch(state);
        if (e->button.button == SDL_BUTTON_LEFT)
            SDL_SetWindowHitTest(state->window.GetWindow(), HitTestCallback, nullptr);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* AppState) {
    ProgramState* state = static_cast<ProgramState*>(AppState);
    state->window.Update(texture, shape);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* AppState, SDL_AppResult Result) {
    delete AppState;
}

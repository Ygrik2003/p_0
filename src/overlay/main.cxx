#include "overlay/overlay_x11.h"

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <spdlog/spdlog.h>

#include <cstdlib>

namespace p0
{
struct app_state
{
    overlay_x11 main_overlay;
};
} // namespace p0

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    p0::app_state* as = new p0::app_state;
    *appstate         = as;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        spdlog::info("Keyboard key down: {0:d}",
                     static_cast<int>(event->key.key));
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    auto& overlay = static_cast<p0::app_state*>(appstate)->main_overlay;

    overlay.iterate();
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {}

int main(int argc, const char** argv)
{

    return EXIT_SUCCESS;
}

#include "overlay.h"

#include <SDL3/SDL.h>

overlay::overlay() noexcept
{
    bool success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_CAMERA |
                            SDL_INIT_EVENTS);
    if (!success)
    {
        // logger SDL_GetError()
    }
}

overlay::~overlay() noexcept {}

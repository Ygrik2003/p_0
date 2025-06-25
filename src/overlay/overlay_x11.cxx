#include "overlay_x11.h"

#include "global.h"

#include <SDL3/SDL.h>
#include <X11/Xlib.h>
#include <libassert/assert.hpp>
#include <spdlog/spdlog.h>

#include <X11/extensions/shape.h>

struct p0::overlay_x11::sdl_details
{
    SDL_Window*   window   = nullptr;
    SDL_Renderer* renderer = nullptr;
};

p0::overlay_x11::overlay_x11() noexcept
    : details{ std::make_unique<sdl_details>() }
{
    SDL_SetAppMetadata(
        p0::global::app_name, p0::global::version, p0::global::identifier);

    bool success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_CAMERA |
                            SDL_INIT_EVENTS);
    ASSERT(success, "Error in SDL_Init call", SDL_GetError());

    success = SDL_CreateWindowAndRenderer(
        p0::global::title,
        1920,
        1080,
        SDL_WINDOW_FULLSCREEN | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_BORDERLESS |
            SDL_WINDOW_ALWAYS_ON_TOP,
        &details->window,
        &details->renderer);
    ASSERT(
        success, "Error in SDL_CreateWindowAndRenderer call", SDL_GetError());
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_SetWindowResizable(details->window, false);

    auto xdisplay = static_cast<Display*>(
        SDL_GetPointerProperty(SDL_GetWindowProperties(details->window),
                               SDL_PROP_WINDOW_X11_DISPLAY_POINTER,
                               NULL));
    auto xwindow = static_cast<Window>(
        SDL_GetNumberProperty(SDL_GetWindowProperties(details->window),
                              SDL_PROP_WINDOW_X11_WINDOW_NUMBER,
                              0));
    ASSERT(xdisplay && xwindow,
           "Error getting x11 window and display",
           xdisplay,
           xwindow);

    XShapeCombineRectangles(
        xdisplay, xwindow, ShapeInput, 0, 0, nullptr, 0, ShapeSet, Unsorted);
    XFlush(xdisplay);
}

p0::overlay_x11::~overlay_x11() noexcept
{
    SDL_DestroyWindow(details->window);
    SDL_DestroyRenderer(details->renderer);
}

void p0::overlay_x11::iterate()
{
    static SDL_FPoint points[500];
    SDL_FRect         rect;

    SDL_SetRenderDrawColor(details->renderer, 0, 0, 0, 0);
    SDL_RenderClear(details->renderer);

    SDL_SetRenderDrawColor(details->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    rect.x = rect.y = 100;
    rect.w          = 440;
    rect.h          = 280;
    SDL_RenderFillRect(details->renderer, &rect);

    SDL_SetRenderDrawColor(details->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderPoints(details->renderer, points, SDL_arraysize(points));

    SDL_SetRenderDrawColor(details->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    rect.x += 30;
    rect.y += 30;
    rect.w -= 60;
    rect.h -= 60;
    SDL_RenderRect(details->renderer, &rect);

    SDL_SetRenderDrawColor(details->renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(details->renderer, 0, 0, 640, 480);
    SDL_RenderLine(details->renderer, 0, 480, 640, 0);

    SDL_RenderPresent(details->renderer);

    auto xdisplay = static_cast<Display*>(
        SDL_GetPointerProperty(SDL_GetWindowProperties(details->window),
                               SDL_PROP_WINDOW_X11_DISPLAY_POINTER,
                               NULL));
}

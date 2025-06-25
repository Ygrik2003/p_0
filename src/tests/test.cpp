#include <SDL3/SDL.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <cstring>
#include <iostream>
#include <vector>

class EventRedirector
{
public:
    EventRedirector()
        : display(nullptr)
        , target_window(0)
        , should_quit(false)
    {
    }

    ~EventRedirector()
    {
        if (display)
        {
            XCloseDisplay(display);
        }
    }

    bool initialize()
    {
        // Initialize SDL
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        {
            std::cerr << "SDL initialization failed: " << SDL_GetError()
                      << std::endl;
            return false;
        }

        // Create a transparent window
        SDL_Window* window =
            SDL_CreateWindow("Event Redirector",
                             640,
                             480,
                             SDL_WINDOW_TRANSPARENT | SDL_WINDOW_BORDERLESS);
        if (!window)
        {
            std::cerr << "Window creation failed: " << SDL_GetError()
                      << std::endl;
            return false;
        }

        // Get X11 display and window
        Display* xdisplay = (Display*)SDL_GetPointerProperty(
            SDL_GetWindowProperties(window),
            SDL_PROP_WINDOW_X11_DISPLAY_POINTER,
            NULL);
        Window xwindow =
            (Window)SDL_GetNumberProperty(SDL_GetWindowProperties(window),
                                          SDL_PROP_WINDOW_X11_WINDOW_NUMBER,
                                          0);

        // Open X11 display
        display = XOpenDisplay(nullptr);
        if (!display)
        {
            std::cerr << "Failed to open X display" << std::endl;
            return false;
        }

        // Find the target window (you'll need to modify this to find your
        // specific window)
        target_window = find_target_window();
        if (!target_window)
        {
            std::cerr << "Failed to find target window" << std::endl;
            return false;
        }

        std::cout << "Initialized successfully. Target window: "
                  << target_window << std::endl;
        return true;
    }

    void run()
    {
        SDL_Event event;
        while (!should_quit)
        {
            while (SDL_PollEvent(&event))
            {
                handle_event(event);
            }
            SDL_Delay(10); // Small delay to prevent busy waiting
        }
    }

private:
    Display* display;
    Window   target_window;
    bool     should_quit;

    Window find_target_window()
    {
        // This is a simple implementation that just returns the root window
        // In a real application, you'd want to find your specific target window
        return DefaultRootWindow(display);
    }

    void handle_event(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                should_quit = true;
                break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
            {
                KeySym  keysym = XStringToKeysym(SDL_GetKeyName(event.key.key));
                KeyCode keycode = XKeysymToKeycode(display, keysym);
                if (keycode)
                {
                    XTestFakeKeyEvent(
                        display,
                        keycode,
                        (event.type == SDL_EVENT_KEY_DOWN) ? True : False,
                        CurrentTime);
                    XFlush(display);
                }
                break;
            }

            case SDL_EVENT_MOUSE_MOTION:
            {
                XTestFakeMotionEvent(
                    display, -1, event.motion.x, event.motion.y, CurrentTime);
                XFlush(display);
                break;
            }

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                unsigned int button = 0;
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        button = 1;
                        break;
                    case SDL_BUTTON_MIDDLE:
                        button = 2;
                        break;
                    case SDL_BUTTON_RIGHT:
                        button = 3;
                        break;
                    default:
                        button = event.button.button;
                        break;
                }

                XTestFakeButtonEvent(
                    display,
                    button,
                    (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) ? True : False,
                    CurrentTime);
                XFlush(display);
                break;
            }

            case SDL_EVENT_MOUSE_WHEEL:
            {
                // Mouse wheel events are often mapped to buttons 4 (up) and 5
                // (down)
                int button = (event.wheel.y > 0) ? 4 : 5;
                int clicks = std::abs(event.wheel.y);

                for (int i = 0; i < clicks; ++i)
                {
                    XTestFakeButtonEvent(display, button, True, CurrentTime);
                    XTestFakeButtonEvent(display, button, False, CurrentTime);
                    XFlush(display);
                }
                break;
            }
        }
    }
};

int main(int argc, char* argv[])
{
    EventRedirector redirector;

    if (!redirector.initialize())
    {
        return 1;
    }

    redirector.run();
    SDL_Quit();
    return 0;
}

// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// angel.rodriguez@esne.edu


#include <SDL.h>
#include <SDL_mixer.h>

#include <OpenGL.hpp>
#include <cassert>
#include <iostream>

#include "../headers/Window.hpp"
#include "../headers/Keyboard.hpp"


Window::Window(const std::string& title, int _width, int _height, bool fullscreen)
{
    window = nullptr;
    gl_context = nullptr;

    width = _width;
    height = _height;


    if (initialize(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
        {
            std::cout << "Error";
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        window = SDL_CreateWindow
        (
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );

        assert(window != nullptr);

        if (window)
        {
            gl_context = SDL_GL_CreateContext(window);

            assert(gl_context != nullptr);

            if (gl_context && glt::initialize_opengl_extensions())
            {
                if (fullscreen)
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
            }
        }
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    }
}

Window::~Window()
{
    if (gl_context) SDL_GL_DeleteContext(gl_context);
    if (window) SDL_DestroyWindow(window);
}

void Window::clear() const
{
    if (gl_context) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap_buffers() const
{
    if (gl_context) SDL_GL_SwapWindow(window);
}


bool Window::poll(Event& event) const
{
    if (window)     // Aunque sería raro, puede llegar a ocurrir que no se haya conseguido crear la ventana...
    {
        // Se extrae un evento usando SDL y se convierte a un evento propio de
        // nuestro engine:

        SDL_Event sdl_event;

        if (SDL_PollEvent(&sdl_event) > 0)
        {
            switch (sdl_event.type)
            {
            case SDL_QUIT:
            {
                event.type = Event::CLOSE;
                break;
            }

            case SDL_KEYDOWN:
            {
                event.type = Event::KEY_PRESSED;
                event.data.keyboard.key_code = engine::Keyboard::translate_sdl_key_code(sdl_event.key.keysym.sym);
                break;
            }

            case SDL_KEYUP:
            {
                event.type = Event::KEY_RELEASED;
                event.data.keyboard.key_code = engine::Keyboard::translate_sdl_key_code(sdl_event.key.keysym.sym);
                break;
            }
            }

            return true;
        }
    }

    return false;
}


int Window::GetWidth()
{
    return width;
}

int Window::GetHeight()
{
    return height;
}



bool Window::initialize(int subsystem)
{
    // Se hace que al salir de la función main() se invoque automáticamente
        // a la función finalize() una vez:

    static bool finalize_is_not_set = true;

    if (finalize_is_not_set)
    {
        finalize_is_not_set = false;

        finalize();
    }

    // Se inicializa el subsistema si no estaba inicializado:

    if (!SDL_WasInit(subsystem))
    {
        return SDL_Init(subsystem) == 0;
    }

    return true;
}

void Window::finalize()
{
    SDL_Quit();
}

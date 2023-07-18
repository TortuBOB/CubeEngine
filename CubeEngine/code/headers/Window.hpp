
// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// angel.rodriguez@esne.edu

#pragma once

#include <string>

class Window 
{
	typedef struct SDL_Window   SDL_Window;
	typedef void* SDL_GLContext;

public:
    /** Esta clase Event es específica para los eventos de la ventana.
      * Por ello está anidada dentro de Window. Se podría generalizar.
      */
    struct Event
    {
        enum Type
        {
            CLOSE,
            KEY_PRESSED,
            KEY_RELEASED
        }
        type;

        union Data
        {
            struct { int key_code; } keyboard;

            struct
            {
                float x, y;
                int   buttons;
            }
            mouse;
        }
        data;
    };

private:
	SDL_Window *window;
	SDL_GLContext gl_context;

	int width;
	int height;

public:
	Window(const std::string& title, int _width, int _height, bool fullscreen = false);
    ~Window();

	/** Borra el buffer de la pantalla usando OpenGL. */
	void clear() const;

	/** Intercambia el buffer visible con el buffer oculto. */
	void swap_buffers() const;

	/** Permite extraer un evento de la cola de eventos asociada a la ventana. */
	bool poll(Event& event) const;

    /** Retorna el ancho actual de la ventana */
	int GetWidth();

    /** Retorna el alto actual de la ventana */
	int GetHeight();

    /** Esta función se llama en aquellos lugares en los que se necesita
      * inicializar algún subsistema de SDL.
      */
    bool initialize(int subsystem);

    /** Esta función se llamará automáticamente al salir de la función main() solo
      * si se inicializa algún subsistema de SDL.
      */
    void finalize();
    
};


/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de gestionar los eventos de la ventana (teclado y el botón de cerrar la ventana)
 *
 */


#pragma once

#include "Window.hpp"
#include "Task.hpp"
#include "MessageDispatcher.hpp"

class InputTask: public Task
{
private:
	/** Puntero a la ventana */
	Window* window;

	/** Sistema que administra mensajes de la escena, para poder mandar mensajes cuando se pulsen teclas */
	std::shared_ptr<MessageDispatcher> messageDispatcher;

public:
	/** Constructor vacio */
	InputTask();

	/**
	 * Constructor que guarda un puntero a la ventana
	 *
	 * @param win es la ventana
	 *
	 */
	InputTask(Window* win);

	/** Función que comprueba los eventos */
	void Run() override;

	/**
	 * Función para guardar el controlador de los mensajes, para poder mandarlos
	 *
	 * @param mDispatcher es el controlador de los mensajes
	 *
	 */
	void SetMessageDispatcher(std::shared_ptr<MessageDispatcher> mDispatcher);
};


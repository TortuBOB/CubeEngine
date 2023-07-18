

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de cerrar la ventana cuando recibe un mensaje
 *
 */


#pragma once

#include "Kernel.hpp"
#include "MessageObserver.hpp"

class CloseMessage : public MessageObserver 
{
private:
	/** Puntero al kernel para poder parar el bucle */
	Kernel* kernel;

public:
	/**
	 * Constructor que recibe el kernel de la esena
	 *
	 * @param taskKernel es el kernel
	 *
	 */
	CloseMessage(Kernel* taskKernel) 
	{
		kernel = taskKernel;
	}

	/**
	 * Función para parar el kernel de tareas y cerrar la ventana
	 *
	 * @param m es el mensaje que recibe
	 *
	 */
	void Handle(Message& m) override 
	{
		kernel->StopLoop();
	}
};
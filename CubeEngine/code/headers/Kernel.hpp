

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de administrar y ejecutar las tasks
 *
 */


#pragma once

#include <vector>
#include <memory>

#include "Task.hpp"


class Kernel 
{
private:
	/** La lista de tareas */
	std::vector<std::shared_ptr<Task>> tasks;
	/** Para finalizar el bucle principal */
	bool exit = false;

public:
	/** Constructor vacio */
	Kernel();

	/** Bucle que ejecuta las tareas */
	void Run();

	/**
	 * Añade una tarea a la lista de tareas
	 *
	 * @param newTask es la tarea que se añade
	 *
	 */
	void AddTask(std::shared_ptr<Task> newTask);

	/** Para el bucle, finaliza el programa */
	void StopLoop();
};


/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta es la clase mensaje que almacena la información de un mensaje
 *
 */


#pragma once

#include<string>

struct Message 
{
public:
	/** El nombre del observer que quiere activar */
	std::string target;

	/** Si un observer tiene varias acciones se cambia esta variable */
	char action = 'n';

	/**
	 * Constructor que recibe el nombre del observer que quiere activar
	 *
	 * @param s es el nombre del observer
	 *
	 */
	Message(std::string s) 
	{
		target = s;
	}
};

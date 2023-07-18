

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Clase abstracta que recive mensajes
 *
 */


#pragma once

#include "Message.hpp"

class MessageObserver 
{
public:
	/** Destructor virtual */
	virtual ~MessageObserver() = default;

	/**
	 * Función que se sobrescribe para que suceda algo al recibir un mensaje
	 *
	 * @param m es el mensaje que se recibe
	 *
	 */
	virtual void Handle(Message& m) = 0;
};


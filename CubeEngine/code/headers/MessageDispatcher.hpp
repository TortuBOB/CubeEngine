

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de administrar los mensajes
 *
 */


#pragma once

#include <memory>
#include <map>
#include <queue>

#include "Task.hpp"
#include "MessageObserver.hpp"


class MessageDispatcher :public Task 
{
private:
	/** El mapa de los observers, con un string como identificador */
	std::map<std::string, std::shared_ptr<MessageObserver>> observers; 

	/** Una lista de los mensajes a procesar */
	std::queue<Message> messages;

public:
	/** Constructor vacio */
	MessageDispatcher() {};

	/**
	 * Función para añadir observers con su identificador
	 *
	 * @param id es el identificador, un string
	 * @param observer es el MessageObserver a añadir
	 *
	 */
	void Register(std::string id, std::shared_ptr<MessageObserver> observer);

	/**
	 * Función que guarda un mensaje en la lista de mensajes para luego procesarlo
	 *
	 * @param message es el mensaje que recibe
	 *
	 */
	void Send(Message message);

	/** Bucle principal que se encarga de procesar los mensajes y activar los observers */
	void Run() override;

	
};



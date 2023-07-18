

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de hacer que un sonido suene cuando llega un mensaje
 *
 */


#pragma once

#include "MessageObserver.hpp"
#include "Sound.hpp"

class SoundMessage : public MessageObserver
{
private:
	/** El sonido */
	Sound audioSystem;

public:
	/**
	 * Constructor que crea el sonido a reproducir
	 *
	 * @param path es el path donde se encuentra el sonido
	 *
	 */
	SoundMessage(const char* path) 
	{
		audioSystem = Sound();
		audioSystem.Load(path);
	}

	/**
	 * Función que hace que el sonido se reproduzca
	 *
	 * @param m es el mensaje que ha recibido
	 *
	 */
	void Handle(Message& m) override 
	{
		audioSystem.PlayAudio();
	}
};


/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de cargar y gestionar un sonido
 *
 */

#pragma once


class Sound 
{
	typedef struct Mix_Chunk Mix_Chunk;
private:
	Mix_Chunk* sound;

public:
	/** Constructor vacio */
	Sound();

	/**
	 * Cargar un sonido .wav
	 *
	 * @param path es el path donde esta el sonido
	 *
	 */
	void Load(const char* path);

	/** Reproducir el sonido */
	void PlayAudio();
};


// Laura Rosas


#include<SDL_mixer.h>
#include <iostream>

#include "../headers/Sound.hpp"


Sound::Sound()
{
    sound = nullptr;
}

void Sound::Load(const char* path)
{
    if (sound = Mix_LoadWAV(path)) 
    {
        std::cout << "Cargado sonido";
    }
}

void Sound::PlayAudio()
{
    if (sound) 
    {
        Mix_PlayChannel(-1, sound, 0);
    }
}



/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de generar y gestionar la escena con sus componentes
 *
 */


#pragma once

#include<iostream>
#include<cstring>

#include "Window.hpp"
#include "Kernel.hpp"
#include "RenderSystem.hpp"
#include "PhysicsSystem.hpp"

#include "MessageDispatcher.hpp"
#include "CloseMessage.hpp"
#include "SoundMessage.hpp"

#include "Entity.hpp"


class Scene
{
private:
    /** Puntero a la ventana */
    Window* window;


    /** La lista de tareas de la escena */
    std::map<std::string, std::shared_ptr<Task>> taskMap;

    /** El kernel de tareas que se encarga de gestionarlas*/
    Kernel kernel;


    /** El mensaje que se encarga de cerrar la ventana */
    std::shared_ptr<CloseMessage> closeMessage;
    /** El mensaje que produce un sonido */
    std::shared_ptr<SoundMessage> soundMessage;


    /** La lista de entidades de la escena */
    std::map<std::string, std::shared_ptr<Entity>> entityMap;

public:
    /**
     * Constructor de la escena, se genera las tareas
     *
     * @param window es la ventana del proyecto
     * @param audioPath es el path donde se encuentra el sonido
     *
     */
    Scene(Window* wind, const char* audioPath);

    /** Carga una escena demo */
    void LoadScene();
    
    /**
     * Carga la escena que este en el path indicado (formato XML)
     *
     * @param path es el path donde se encuentra el archivo de la escena
     *
     */
    bool LoadScene(std::string path);

    /** Llama al kernel para que se ejecuten el bucle de las tareas  */
    void Run();

    /** Devuelve la lista de entidades de la escena */
    std::map<std::string, std::shared_ptr<Entity>> GetMap();

    /** Devuelve el sistema de fisicas de la escena */
    PhysicsSystem* GetPhysicsSystem();
    /** Devuelve el sistema de render de la escena */
    RenderSystem* GetRenderSystem();
    /** Devuelve el sistema que administra mensajes de la escena */
    MessageDispatcher* GetMessageDispatcher();
};
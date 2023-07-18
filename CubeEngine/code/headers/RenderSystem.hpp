

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de gestionar los componentes que se pueden renderizar
 *
 */


#pragma once

#include <Render_Node.hpp>
#include <memory>
#include <vector>

#include "Task.hpp"
#include "Window.hpp"
#include "Entity.hpp"


class RenderSystem : public Task
{
private:
    /** Puntero a la ventana */
    Window* window;
    /** La escena donde estan los modelos */
    std::shared_ptr<glt::Render_Node> renderer;

    /** Lista de las entidades con un render component */
    std::vector<std::shared_ptr<Entity>> allRenderableEntities;
    /** La camara de la escena */
    std::shared_ptr<Entity> cameraEntity;
    /** La luz de la escena */
    std::shared_ptr<Entity> lightEntity;


public:
    /**
     * Constructor del sistema de render
     *
     * @param newComponent es la entidad que se va a añadir
     *
     */
    RenderSystem(Window* wind);

    /** Ejecución de las funciones de update y render */
    void Run() override;

    /** Función para renderizar las entidades */
    void Render();
    /** Actualiza la posición del render al transform de la entidad */
    void UpdateTransform();

    /** Función que devuelve el render node */
    std::shared_ptr<glt::Render_Node> GetRenderer(){return renderer;}

    /**
     * Función que añade las entidades que tienen componente de render
     *
     * @param newEntity es la entidad que se va a añadir
     *
     */
    void AddRenderableEntity(std::shared_ptr<Entity> newEntity);

    /**
     * Función para añadir la camara de la escena
     *
     * @param camera es la camara a añadir
     *
     */
    void SetCameraEntity(std::shared_ptr<Entity> camera);

    /**
     * Función que añade laluz de la escena
     *
     * @param light es luz a añadir
     *
     */
    void SetLightEntity(std::shared_ptr<Entity> light);
};
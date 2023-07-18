

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
     * @param newComponent es la entidad que se va a a�adir
     *
     */
    RenderSystem(Window* wind);

    /** Ejecuci�n de las funciones de update y render */
    void Run() override;

    /** Funci�n para renderizar las entidades */
    void Render();
    /** Actualiza la posici�n del render al transform de la entidad */
    void UpdateTransform();

    /** Funci�n que devuelve el render node */
    std::shared_ptr<glt::Render_Node> GetRenderer(){return renderer;}

    /**
     * Funci�n que a�ade las entidades que tienen componente de render
     *
     * @param newEntity es la entidad que se va a a�adir
     *
     */
    void AddRenderableEntity(std::shared_ptr<Entity> newEntity);

    /**
     * Funci�n para a�adir la camara de la escena
     *
     * @param camera es la camara a a�adir
     *
     */
    void SetCameraEntity(std::shared_ptr<Entity> camera);

    /**
     * Funci�n que a�ade laluz de la escena
     *
     * @param light es luz a a�adir
     *
     */
    void SetLightEntity(std::shared_ptr<Entity> light);
};


/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase es el componente que se encarga de renderizar
 *
 */


#pragma once

#include <iostream>
#include <memory>

#include <Model.hpp>
#include <Render_Node.hpp>

#include "Component.hpp"
#include "TransformComponent.hpp"


class RenderableComponent : public Component
{
private:
    /** El modelo */
    std::shared_ptr<glt::Model> model;
    /** El nombre del componente (para insertar en el render node) */
    std::string compName;
    /** El color del modelo */
    glt::Vector3 color;
    /** El material del modelo */
    std::shared_ptr<glt::Material> material;

public:
    /** Constructor vacio */
    RenderableComponent();

    /**
     * Constructor que guarda el nombre y color del modelo
     *
     * @param name es el nombre del componente
     * @param col es el color que se aplicará al modelo
     *
     */
    RenderableComponent(std::string name, glt::Vector3 col);

    /**
     * Función que crea un cubo como modelo
     *
     * @param _scene es el render node donde se va a introducir el modelo
     *
     */
    void CubeComponent(std::shared_ptr<glt::Render_Node> _scene);

    /**
     * Función que actualiza el modelo a la posición del transform
     *
     * @param transform es el transform de la entidad
     *
     */
    void UpdateModelTransform(TransformComponent* transform);
};


/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de generar entidades con sus componentes
 *
 */

#pragma once

#include <iostream>
#include <memory>
#include <map>

#include "Component.hpp"
#include "TransformComponent.hpp"

class Entity
{
    
private:
    /** La lista de componentes de la entidad */
    std::map<std::string, std::shared_ptr<Component>> componentMap;

public:
    /** Constructor de la entidad que genera el componente transform */
    Entity();

    /**
     * Funcion para añadir un componente a una entidad
     *
     * @param name es el nombre del componente
     * @param newComp es el nuevo componente que se desea añadir
     *
     */
    void AddComponent(std::string nameComp, std::shared_ptr<Component> newComp);

    /**
     * Devuelve un componente por su nombre
     *
     * @param componentName es el nombre del componente
     *
     */
    std::shared_ptr<Component> GetComponent(std::string componentName);

    /** Funcion que devuelve el componente transform de la entidad */
    TransformComponent* GetTransform();

};


/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase que representa el componente transform de una entidad
 *
 */


#pragma once

#include <Math.hpp>
#include "Component.hpp"


class TransformComponent : public Component
{
private:
    glt::Vector3 position;
    glt::Vector3 rotation;
    glt::Vector3 compScale;

public:
    /** Constructor que inicializa posición y rotación a 0, y escala a 1 */
    TransformComponent();


    /**
     * Función para cambiar la posición
     *
     * @param pos es la nueva posición
     *
     */
    void SetPosition(glt::Vector3 pos);

    /** Función que devuelve la posición */
    glt::Vector3 GetPosition();


    /**
     * Función para cambiar la rotacion
     *
     * @param rot es la nueva rotacion
     *
     */
    void SetRotation(glt::Vector3 rot);

    /** Función que devuelve la rotacion */
    glm::vec3 GetRotation();


    /**
     * Función para cambiar la escala
     *
     * @param s es la nueva escala
     *
     */
    void SetScale(glt::Vector3 s);

    /**
     * Función para cambiar la escala
     *
     * @param s es la nueva escala, igual en todos los ejes
     *
     */
    void SetScale(float s);

    /** Función que devuelve la escala */
    glt::Vector3 GetScale();


    /** Función que devuelve la matriz de transformación */
    glt::Matrix44 GetTransformMatrix();

};


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
    /** Constructor que inicializa posici�n y rotaci�n a 0, y escala a 1 */
    TransformComponent();


    /**
     * Funci�n para cambiar la posici�n
     *
     * @param pos es la nueva posici�n
     *
     */
    void SetPosition(glt::Vector3 pos);

    /** Funci�n que devuelve la posici�n */
    glt::Vector3 GetPosition();


    /**
     * Funci�n para cambiar la rotacion
     *
     * @param rot es la nueva rotacion
     *
     */
    void SetRotation(glt::Vector3 rot);

    /** Funci�n que devuelve la rotacion */
    glm::vec3 GetRotation();


    /**
     * Funci�n para cambiar la escala
     *
     * @param s es la nueva escala
     *
     */
    void SetScale(glt::Vector3 s);

    /**
     * Funci�n para cambiar la escala
     *
     * @param s es la nueva escala, igual en todos los ejes
     *
     */
    void SetScale(float s);

    /** Funci�n que devuelve la escala */
    glt::Vector3 GetScale();


    /** Funci�n que devuelve la matriz de transformaci�n */
    glt::Matrix44 GetTransformMatrix();

};
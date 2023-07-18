

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta es la clase abstacta de la que heredan los componentes
 *
 */


#pragma once


class Component
{
public:
    /** Constructor vacio */
    Component() {};

    /** Destructor virtual */
    virtual ~Component() = default;
};
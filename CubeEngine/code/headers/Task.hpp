

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Clase abstracta de la que heredan las tareas
 *
 */


#pragma once


class Task
{
public:
    /** Constructor vacio */
    Task() {};
    
    /** Destructor virtual */
    virtual ~Task() = default;

    /** Función que luego sobreescriben las tareas para ejecutar sus acciones */
    virtual void Run() {};
};
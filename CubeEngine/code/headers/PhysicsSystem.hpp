

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de gestionar las físicas de las entidades físicas
 *
 */


#pragma once

#include <btBulletDynamicsCommon.h>
#include <memory>
#include <vector>

#include "Task.hpp"
#include "Entity.hpp"
#include "PhysicsComponent.hpp"
#include "MessageDispatcher.hpp"


class PhysicsSystem : public Task
{
private:
    //Para crear el mundo físico de bullet
    std::shared_ptr <btDefaultCollisionConfiguration> collisionConfiguration;
    std::shared_ptr <btCollisionDispatcher> collisionDispatcher;
    std::shared_ptr <btDbvtBroadphase> overlappingPairCache;
    std::shared_ptr <btSequentialImpulseConstraintSolver> constraintSolver;
    /** El mundo que emula las físicas */
    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld;


    /** Lista de las entidades que tienen componente físico */
    std::vector<std::shared_ptr<Entity>> allPhysicsEntities;


    //Colisiones
    /** Sistema que administra mensajes de la escena, para poder mandar mensajes en las colisiones */
    std::shared_ptr<MessageDispatcher> messageDispatcher;
    /** Guarda las entidades con id/tag "Wall" para detectar las colisiones */
    std::vector<PhysicsComponent*> walls;
    /** Guarda el componente físico del player para comprobar colisiones */
    PhysicsComponent* player;

public:
    /** Constructor que crea el mundo de las físicas */
    PhysicsSystem();

    /** Función que simula las físicas y llama a las funciones update y check collisions */
    void Run() override;

    /** Aplica la simulación física de las entidades a su transform */
    void UpdateTransform();
    /** Función que comprueba las colisiones */
    void CheckCollisions();

    /** Función que devuelve el mundo físico */
    std::shared_ptr<btDiscreteDynamicsWorld> GetWorld();

    /**
     * Función que añade las entidades que tienen componente físico
     *
     * @param newComponent es la entidad que se va a añadir
     *
     */
    void AddPhysicEntity(std::shared_ptr<Entity> newComponent);

    /** Función para hacer reset al mundo físico, ya que es necesario detrutirlo lo primero */
    void EndWorld();

    /**
     * Función para guardar el controlador de los mensajes, para poder mandarlos
     *
     * @param mDispatcher es el controlador de los mensajes
     *
     */
    void SetMessageDispatcher(std::shared_ptr<MessageDispatcher> mDispatcher);
};
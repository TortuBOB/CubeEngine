

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase se encarga de gestionar las f�sicas de las entidades f�sicas
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
    //Para crear el mundo f�sico de bullet
    std::shared_ptr <btDefaultCollisionConfiguration> collisionConfiguration;
    std::shared_ptr <btCollisionDispatcher> collisionDispatcher;
    std::shared_ptr <btDbvtBroadphase> overlappingPairCache;
    std::shared_ptr <btSequentialImpulseConstraintSolver> constraintSolver;
    /** El mundo que emula las f�sicas */
    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld;


    /** Lista de las entidades que tienen componente f�sico */
    std::vector<std::shared_ptr<Entity>> allPhysicsEntities;


    //Colisiones
    /** Sistema que administra mensajes de la escena, para poder mandar mensajes en las colisiones */
    std::shared_ptr<MessageDispatcher> messageDispatcher;
    /** Guarda las entidades con id/tag "Wall" para detectar las colisiones */
    std::vector<PhysicsComponent*> walls;
    /** Guarda el componente f�sico del player para comprobar colisiones */
    PhysicsComponent* player;

public:
    /** Constructor que crea el mundo de las f�sicas */
    PhysicsSystem();

    /** Funci�n que simula las f�sicas y llama a las funciones update y check collisions */
    void Run() override;

    /** Aplica la simulaci�n f�sica de las entidades a su transform */
    void UpdateTransform();
    /** Funci�n que comprueba las colisiones */
    void CheckCollisions();

    /** Funci�n que devuelve el mundo f�sico */
    std::shared_ptr<btDiscreteDynamicsWorld> GetWorld();

    /**
     * Funci�n que a�ade las entidades que tienen componente f�sico
     *
     * @param newComponent es la entidad que se va a a�adir
     *
     */
    void AddPhysicEntity(std::shared_ptr<Entity> newComponent);

    /** Funci�n para hacer reset al mundo f�sico, ya que es necesario detrutirlo lo primero */
    void EndWorld();

    /**
     * Funci�n para guardar el controlador de los mensajes, para poder mandarlos
     *
     * @param mDispatcher es el controlador de los mensajes
     *
     */
    void SetMessageDispatcher(std::shared_ptr<MessageDispatcher> mDispatcher);
};
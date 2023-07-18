

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase es el componente que da físicas a una entidad
 *
 */


#pragma once

#include <iostream>
#include <memory>

#include <btBulletDynamicsCommon.h>
#include <Math.hpp>

#include "Component.hpp"
#include "TransformComponent.hpp"


class PhysicsComponent : public Component
{
private:
	/** Un identificador para comprobar colisiones */
	std::string collisionId = "";

	/** El cuerpo rigido de la entidad */
	std::shared_ptr<btRigidBody> rigidBody;
	/** La forma del cuerpo rigido */
	std::shared_ptr<btCollisionShape> shape;
	/** El motion state del cuerpo rigido */
	std::shared_ptr<btMotionState> motionState;

	/** Un puntero al transform de la entidad */
	TransformComponent* entityTransform;

public:
	/**
	 * Constructor que guarda un puntero al transform de la entidad
	 *
	 * @param transf es el transform de la entidad
	 *
	 */
	PhysicsComponent(TransformComponent* transf);

	/**
	 * Crear un rigidbody con forma de cubo
	 *
	 * @param dynamicsWorld es el mundo físico
	 * @param size es el tamaño del cubo
	 * @param mass es la masa del cuerpo rígido, 0 es un cuerpo estático
	 *
	 */
	void CreateBoxCollider(std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld, glt::Vector3 size, double mass);

	/**
	 * Función para poner un id de colisión al componente
	 *
	 * @param id es el identificador
	 *
	 */
	void SetCollisionId(std::string id);

	/** Función que devuelve la id para comprobar colisiones */
	std::string GetCollisionId();

	/** Función que devuelve el rigidbody del componente */
	std::shared_ptr<btRigidBody> GetRigidbody();
};
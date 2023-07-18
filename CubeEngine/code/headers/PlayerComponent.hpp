

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase es el componente que permite al usuario controlar la entidad
 *
 */


#pragma once

#include "Component.hpp"
#include "MessageObserver.hpp"
#include "PhysicsComponent.hpp"

class PlayerComponent : public Component, public MessageObserver
{
private:
	/** La velocidad a la que se va a mover el player */
	float speed = 0.5;

	/** Puntero al componente de físicas */
	PhysicsComponent* entityPhysics;

public:
	/**
	 * Constructor que gurada el componente de físicas y establece la velocidad
	 *
	 * @param compPhysics el componente de físicas de la entidad
	 * @param moveSpeed la velocidad de movimiento
	 *
	 */
	PlayerComponent(PhysicsComponent* compPhysics, float moveSpeed);

	/**
	 * Función para mover el jugador, funciona por mensajes y dependiendo de la acción del mensaje 
	 * se movera en distintas direcciones
	 *
	 * @param m es el mensaje que recibe
	 *
	 */
	void Handle(Message& m) override;

};


// Laura Rosas


#include "../headers/PlayerComponent.hpp"


PlayerComponent::PlayerComponent(PhysicsComponent* compPhysics, float moveSpeed)
{
	entityPhysics = compPhysics;
	speed = moveSpeed;
}

void PlayerComponent::Handle(Message& m)
{
	float z = 0;
	float x = 0;

	//Dependiendo de la acción del mensaje se harán cosas distintas
	switch (m.action)
	{
		//-----------------PULSAR TECLAS-----------------//
	case 'u': //up
		x = entityPhysics->GetRigidbody()->getLinearVelocity().x();
		entityPhysics->GetRigidbody()->setLinearVelocity(btVector3(x, 0, -speed));
		break;
	case 'l': //left
		z = entityPhysics->GetRigidbody()->getLinearVelocity().z();
		entityPhysics->GetRigidbody()->setLinearVelocity(btVector3(-speed, 0, z)); 
		break;
	case 'd': //down
		x = entityPhysics->GetRigidbody()->getLinearVelocity().x();
		entityPhysics->GetRigidbody()->setLinearVelocity(btVector3(x, 0, speed));
		break;
	case 'r': //right
		z = entityPhysics->GetRigidbody()->getLinearVelocity().z();
		entityPhysics->GetRigidbody()->setLinearVelocity(btVector3(speed, 0, z));
		break;

		//-----------------SOLTAR TECLAS-----------------//
	case 'x': //eje x
		z = entityPhysics->GetRigidbody()->getLinearVelocity().z();
		entityPhysics->GetRigidbody()->setLinearVelocity(btVector3(0, 0, z));
		break;
	case 'z': //eje xz
		x = entityPhysics->GetRigidbody()->getLinearVelocity().x();
		entityPhysics->GetRigidbody()->setLinearVelocity(btVector3(x, 0, 0));
		break;

	default:
		entityPhysics->GetRigidbody()->setLinearVelocity(btVector3(0, 0, 0));
		break;
	}
}



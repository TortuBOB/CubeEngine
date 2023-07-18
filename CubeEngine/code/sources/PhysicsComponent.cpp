

// Laura Rosas


#include "../headers/PhysicsComponent.hpp"

using namespace std;


PhysicsComponent::PhysicsComponent(TransformComponent* transf)
{
	rigidBody = nullptr;
	shape = nullptr;
	motionState = nullptr;
	entityTransform = transf;
}

void PhysicsComponent::CreateBoxCollider(std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld, glt::Vector3 size, double mass)
{
	//RigidBody
	shape = make_shared< btBoxShape >(btVector3(size.x, size.y, size.z));

	btTransform transform;
	transform.setIdentity();
	btQuaternion rotation;
	rotation.setEuler(glm::radians(entityTransform->GetRotation().x), glm::radians(entityTransform->GetRotation().y), glm::radians(entityTransform->GetRotation().z));
	transform.setRotation(rotation);
	transform.setOrigin(btVector3(entityTransform->GetPosition().x, entityTransform->GetPosition().y, entityTransform->GetPosition().z));
	//transform.setOrigin(btVector3(0, 0, 0));

	btVector3 localInertia(0, 0, 0);

	shape->calculateLocalInertia(mass, localInertia);

	motionState = make_shared <btDefaultMotionState >(transform);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motionState.get(), shape.get(), localInertia);

	rigidBody = make_shared< btRigidBody >(info);

	rigidBody->setRestitution(0.0);
	rigidBody->setFriction(0.1);

	//Que no se desactiven los dinamicos
	if (mass > 0) 
	{
		rigidBody->setActivationState(DISABLE_DEACTIVATION);
	}

	dynamicsWorld->addRigidBody(rigidBody.get());

	
}

void PhysicsComponent::SetCollisionId(std::string id)
{
	collisionId = id;
}

std::string PhysicsComponent::GetCollisionId()
{
	return collisionId;
}

std::shared_ptr<btRigidBody> PhysicsComponent::GetRigidbody()
{
	return rigidBody;
}

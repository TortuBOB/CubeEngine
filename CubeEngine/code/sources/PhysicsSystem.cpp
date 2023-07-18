

// Laura Rosas


#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "../headers/PhysicsSystem.hpp"
#include "../headers/TransformComponent.hpp"
#include "../headers/PhysicsComponent.hpp"
#include "../headers/Message.hpp"


PhysicsSystem::PhysicsSystem()
{
    collisionConfiguration = std::make_shared<btDefaultCollisionConfiguration>();

    collisionDispatcher = std::make_shared<btCollisionDispatcher>(collisionConfiguration.get());

    overlappingPairCache = std::make_shared<btDbvtBroadphase>();

    constraintSolver = std::make_shared<btSequentialImpulseConstraintSolver>();

    dynamicsWorld = std::make_shared<btDiscreteDynamicsWorld>
    (
        collisionDispatcher.get(),
        overlappingPairCache.get(),
        constraintSolver.get(),
        collisionConfiguration.get()
    );

    dynamicsWorld->setGravity(btVector3(0, -0.04f, 0));
    dynamicsWorld->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
}

void PhysicsSystem::Run()
{
    //Step del mundo fisico
    dynamicsWorld->stepSimulation(1.f / 60.f);

    //Actualizar el transform de los componentes
    UpdateTransform();

    //Mirar colisiones
    CheckCollisions();
}

void PhysicsSystem::UpdateTransform()
{
    for (size_t i = 0; i < allPhysicsEntities.size(); i++)
    {
        std::shared_ptr<Entity> ent = allPhysicsEntities[i];
        PhysicsComponent* physicsComp = static_cast<PhysicsComponent*>(ent->GetComponent("Physics").get());

        if (physicsComp->GetRigidbody()->isKinematicObject() || physicsComp->GetRigidbody()->isActive())
        {
            TransformComponent* transfComp = ent->GetTransform();
            btTransform physics_transform;

            physicsComp->GetRigidbody()->getMotionState()->getWorldTransform(physics_transform);

            glt::Matrix44 graphics_transform;

            physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

            //Sacar la posicion
            transfComp->SetPosition(graphics_transform[3]);

            //sacar la rotacion
            glt::Quaternion quaternion = glt::extract_rotation(graphics_transform);
            glt::Vector3 rotVec = glm::degrees(glm::eulerAngles(quaternion));

            transfComp->SetRotation(rotVec);
        }

    }
}

void PhysicsSystem::CheckCollisions()
{
    int manifold_count = dynamicsWorld->getDispatcher()->getNumManifolds();
    for (int i = 0; i < manifold_count; i++)
    {
        btPersistentManifold* manifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* object_a = (btCollisionObject*)(manifold->getBody0());
        btCollisionObject* object_b = (btCollisionObject*)(manifold->getBody1());
        int numContacts = manifold->getNumContacts();
        for (int j = 0; j < numContacts; j++)
        {
            btManifoldPoint& point = manifold->getContactPoint(j);
            if (point.getDistance() < 0.f)
            {
                //Si impacata una pared con el player
                for (PhysicsComponent* phC : walls) 
                {
                    if (object_a == phC->GetRigidbody().get() && object_b == player->GetRigidbody().get() ||
                        object_a == player->GetRigidbody().get() && object_b == phC->GetRigidbody().get()) 
                    {
                        Message mes = Message("Sound");
                        messageDispatcher->Send(mes);
                    }
                }

                //Si impacta un enemigo con el player
               
            }
        }
    }
}

std::shared_ptr<btDiscreteDynamicsWorld> PhysicsSystem::GetWorld()
{
    return dynamicsWorld;
}

void PhysicsSystem::AddPhysicEntity(std::shared_ptr<Entity> newComponent)
{
    allPhysicsEntities.push_back(newComponent);
    PhysicsComponent* physicsComp = static_cast<PhysicsComponent*>(newComponent->GetComponent("Physics").get());

    if (physicsComp->GetCollisionId() == "Wall") 
    {
        walls.push_back(physicsComp);
    }
    else if (physicsComp->GetCollisionId() == "Player") 
    {
        player = physicsComp;
    }
}

void PhysicsSystem::EndWorld()
{
    dynamicsWorld.reset();
}

void PhysicsSystem::SetMessageDispatcher(std::shared_ptr<MessageDispatcher> mDispatcher)
{
    messageDispatcher = mDispatcher;
}

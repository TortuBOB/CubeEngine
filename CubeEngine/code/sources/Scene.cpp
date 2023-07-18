

// Laura Rosas


#include <string>
#include <fstream>
#include <sstream>
#include <rapidxml.hpp>

#include "../headers/Scene.hpp"
#include "../headers/Entity.hpp"

#include "../headers/RenderableComponent.hpp"
#include "../headers/CameraComponent.hpp"
#include "../headers/TransformComponent.hpp"
#include "../headers/LightComponent.hpp"
#include "../headers/PhysicsComponent.hpp"
#include "../headers/PlayerComponent.hpp"

#include "../headers/RenderSystem.hpp"
#include "../headers/PhysicsSystem.hpp"
#include "../headers/InputTask.hpp"

using namespace rapidxml;


Scene::Scene(Window* wind, const char * audioPath)
{
	window = wind;
	kernel = Kernel();
	

	//Inputs de teclado
	std::shared_ptr<InputTask> inputTask = std::make_shared<InputTask>(window);
	

	//Mensajes
	std::shared_ptr<MessageDispatcher> messageDispatcher = std::make_shared<MessageDispatcher>();

	//Guardar el dispatcher en el input task
	inputTask->SetMessageDispatcher(messageDispatcher);

	taskMap.insert(std::pair<std::string, std::shared_ptr<Task>>("InputTask", inputTask));
	kernel.AddTask(inputTask);

	taskMap.insert(std::pair<std::string, std::shared_ptr<Task>>("MessageDispatcher", messageDispatcher));
	kernel.AddTask(messageDispatcher);

	
	//Simulacion fisica
	std::shared_ptr<PhysicsSystem> physicsSystem = std::make_shared<PhysicsSystem>();
	physicsSystem->SetMessageDispatcher(messageDispatcher);
	taskMap.insert(std::pair<std::string, std::shared_ptr<Task>>("PhysicsSystem", physicsSystem));
	kernel.AddTask(physicsSystem);

	//Tarea renderer
	std::shared_ptr<RenderSystem> renderSystem = std::make_shared<RenderSystem>(wind);
	taskMap.insert(std::pair<std::string, std::shared_ptr<Task>>("RenderSystem", renderSystem));
	kernel.AddTask(renderSystem);

	//Añadir mensaje para cerrar la ventana
	closeMessage = std::make_shared<CloseMessage>(&kernel);
	GetMessageDispatcher()->Register("Close", closeMessage);

	//mensaje de sonido
	soundMessage = std::make_shared<SoundMessage>(audioPath);
	GetMessageDispatcher()->Register("Sound", soundMessage);

}

void Scene::LoadScene()
{
	//-----------------------------------------CAMARA-----------------------------------------//
	std::shared_ptr < Entity >cameraEntity = std::make_shared<Entity>();
	cameraEntity->GetTransform()->SetPosition(glt::Vector3(0, 30, 40)); 
	cameraEntity->GetTransform()->SetRotation(glt::Vector3(-45, 0, 0)); 
	float aspecRatio = float(window->GetWidth()) / window->GetHeight();
	std::shared_ptr<CameraComponent> cameraComponent = 
		std::make_shared<CameraComponent>(glm::radians(60.0f), 1.f, 70.f, aspecRatio, GetRenderSystem()->GetRenderer());
	cameraEntity->AddComponent("Camera", cameraComponent);
	GetRenderSystem()->SetCameraEntity(cameraEntity);
	entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >("Camera", cameraEntity));

	//-----------------------------------------LUZ-----------------------------------------//
	std::shared_ptr<Entity> lightEntity = std::make_shared<Entity>();
	lightEntity->GetTransform()->SetPosition(glt::Vector3(10.f, 10.f, 10.f));
	std::shared_ptr<LightComponent> lightComponent = std::make_shared<LightComponent>(GetRenderSystem()->GetRenderer(), lightEntity->GetTransform());
	lightEntity->AddComponent("Light", lightComponent);
	entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >("Light", lightEntity));

	//-----------------------------------------ESCENARIO-----------------------------------------//
	//SUELO
	std::shared_ptr<Entity> cubeFloor = std::make_shared<Entity>();
	cubeFloor->GetTransform()->SetPosition(glt::Vector3(0, -6, 0));
	cubeFloor->GetTransform()->SetScale(glt::Vector3(20, 0.3, 20));

	std::shared_ptr<RenderableComponent> cubeFRend = std::make_shared<RenderableComponent>("cubeFloor", glt::Vector3(0.4f, 0.65f, 0.9f));
	cubeFRend->CubeComponent(GetRenderSystem()->GetRenderer());
	cubeFloor->AddComponent("Renderable", cubeFRend);
	GetRenderSystem()->AddRenderableEntity(cubeFloor);
	
	std::shared_ptr<PhysicsComponent> floorPh = std::make_shared<PhysicsComponent>(cubeFloor->GetTransform());
	floorPh->CreateBoxCollider(GetPhysicsSystem()->GetWorld(), cubeFloor->GetTransform()->GetScale(), 0);
	cubeFloor->AddComponent("Physics", floorPh);
	GetPhysicsSystem()->AddPhysicEntity(cubeFloor);

	entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >("CubeFloor", cubeFloor));

	//PAREDES
	glt::Vector3 wallColor(0.1f, 0.4f, 0.9f);

	//PARED DERECHA
	std::shared_ptr<Entity> cubeRightWall = std::make_shared<Entity>();
	cubeRightWall->GetTransform()->SetPosition(glt::Vector3(20, -3, 0));
	cubeRightWall->GetTransform()->SetScale(glt::Vector3(0.5, 3.3, 20));

	std::shared_ptr<RenderableComponent> cubeRWRend = std::make_shared<RenderableComponent>("CubeRightWall", wallColor);
	cubeRWRend->CubeComponent(GetRenderSystem()->GetRenderer());
	cubeRightWall->AddComponent("Renderable", cubeRWRend);
	GetRenderSystem()->AddRenderableEntity(cubeRightWall);

	std::shared_ptr<PhysicsComponent> cubeRWPh = std::make_shared<PhysicsComponent>(cubeRightWall->GetTransform());
	cubeRWPh->CreateBoxCollider(GetPhysicsSystem()->GetWorld(), cubeRightWall->GetTransform()->GetScale(), 0);
	cubeRWPh->SetCollisionId("Wall");
	cubeRightWall->AddComponent("Physics", cubeRWPh);
	GetPhysicsSystem()->AddPhysicEntity(cubeRightWall);

	entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >("CubeRightWall", cubeRightWall));

	//PARED IZQUIERDA
	std::shared_ptr<Entity> cubeLeftWall = std::make_shared<Entity>();
	cubeLeftWall->GetTransform()->SetPosition(glt::Vector3(-20, -3, 0));
	cubeLeftWall->GetTransform()->SetScale(glt::Vector3(0.5, 3.3, 20));

	std::shared_ptr<RenderableComponent> cubeLWRend = std::make_shared<RenderableComponent>("cubeLeftWall", wallColor);
	cubeLWRend->CubeComponent(GetRenderSystem()->GetRenderer());
	cubeLeftWall->AddComponent("Renderable", cubeLWRend);
	GetRenderSystem()->AddRenderableEntity(cubeLeftWall);

	std::shared_ptr<PhysicsComponent> cubeLWPhy = std::make_shared<PhysicsComponent>(cubeLeftWall->GetTransform());
	cubeLWPhy->CreateBoxCollider(GetPhysicsSystem()->GetWorld(), cubeLeftWall->GetTransform()->GetScale(), 0);
	cubeLWPhy->SetCollisionId("Wall");
	cubeLeftWall->AddComponent("Physics", cubeLWPhy);
	GetPhysicsSystem()->AddPhysicEntity(cubeLeftWall);

	entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >("cubeLeftWall", cubeLeftWall));

	//PARED ARRIBA
	std::shared_ptr<Entity> cubeUpWall = std::make_shared<Entity>();
	cubeUpWall->GetTransform()->SetPosition(glt::Vector3(0, -3, -20));
	cubeUpWall->GetTransform()->SetScale(glt::Vector3(20, 3.3, 0.5));

	std::shared_ptr<RenderableComponent> cubeUWRend = std::make_shared<RenderableComponent>("cubeUpWall", wallColor);
	cubeUWRend->CubeComponent(GetRenderSystem()->GetRenderer());
	cubeUpWall->AddComponent("Renderable", cubeUWRend);
	GetRenderSystem()->AddRenderableEntity(cubeUpWall);

	std::shared_ptr<PhysicsComponent> cubeUWPhy = std::make_shared<PhysicsComponent>(cubeUpWall->GetTransform());
	cubeUWPhy->CreateBoxCollider(GetPhysicsSystem()->GetWorld(), cubeUpWall->GetTransform()->GetScale(), 0);
	cubeUWPhy->SetCollisionId("Wall");
	cubeUpWall->AddComponent("Physics", cubeUWPhy);
	GetPhysicsSystem()->AddPhysicEntity(cubeUpWall);

	entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >("cubeUpWall", cubeUpWall));

	//PARED ABAJO
	std::shared_ptr<Entity> cubeDownWall = std::make_shared<Entity>();
	cubeDownWall->GetTransform()->SetPosition(glt::Vector3(0, -3, 20));
	cubeDownWall->GetTransform()->SetScale(glt::Vector3(20, 3.3, 0.5));

	std::shared_ptr<RenderableComponent> cubeDWRend = std::make_shared<RenderableComponent>("cubeDownWall", wallColor);
	cubeDWRend->CubeComponent(GetRenderSystem()->GetRenderer());
	cubeDownWall->AddComponent("Renderable", cubeDWRend);
	GetRenderSystem()->AddRenderableEntity(cubeDownWall);

	std::shared_ptr<PhysicsComponent> cubeDWPhy = std::make_shared<PhysicsComponent>(cubeDownWall->GetTransform());
	cubeDWPhy->CreateBoxCollider(GetPhysicsSystem()->GetWorld(), cubeDownWall->GetTransform()->GetScale(), 0);
	cubeDWPhy->SetCollisionId("Wall");
	cubeDownWall->AddComponent("Physics", cubeDWPhy);
	GetPhysicsSystem()->AddPhysicEntity(cubeDownWall);

	entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >("cubeDownWall", cubeDownWall));


	//-----------------------------------------"PERSONAJES"-----------------------------------------//
	//CUBO DINAMICO
	std::shared_ptr<Entity> cubePhysics = std::make_shared<Entity>();
	cubePhysics->GetTransform()->SetPosition(glt::Vector3(0, 3, 0));
	//cubePhysics->GetTransform()->SetRotation(glt::Vector3(0.f, 0, 0));
	cubePhysics->GetTransform()->SetScale(1.5);

	std::shared_ptr<RenderableComponent> cubeRendTwo = std::make_shared<RenderableComponent>("cuboPhysics", glt::Vector3(1.0f, 0.7f, 0.0f));
	cubeRendTwo->CubeComponent(GetRenderSystem()->GetRenderer());
	cubePhysics->AddComponent("Renderable", cubeRendTwo);
	GetRenderSystem()->AddRenderableEntity(cubePhysics);
	
	std::shared_ptr<PhysicsComponent> cubPhys = std::make_shared<PhysicsComponent>(cubePhysics->GetTransform());
	cubPhys->CreateBoxCollider(GetPhysicsSystem()->GetWorld(), cubePhysics->GetTransform()->GetScale(), 1);
	cubPhys->SetCollisionId("Player");
	cubePhysics->AddComponent("Physics", cubPhys);
	GetPhysicsSystem()->AddPhysicEntity(cubePhysics);

	std::shared_ptr<PlayerComponent> playerComponent = std::make_shared<PlayerComponent>(cubPhys.get(), 0.5f);
	cubePhysics->AddComponent("Player", playerComponent);
	GetMessageDispatcher()->Register("Player", playerComponent);

	entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >("cubePhysics", cubePhysics));
}


bool Scene::LoadScene(std::string path)
{
	//Leer el XML y sacar el document
	xml_document<>* doc = new xml_document<>();;
	std::ifstream file(path.c_str());
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc->parse<0>(&content[0]);

	if (!doc) 
	{
		return false;
	}

	//Nodo raiz 
	xml_node<>* scene = doc->first_node("scene");
	if (!scene) 
	{
		return false;
	}
	for (xml_node<>* eNode = scene->first_node("entity"); eNode; eNode = eNode->next_sibling())
	{
		std::shared_ptr<Entity> entity = std::make_shared<Entity>();

		//El nombre
		xml_attribute<>* nameAttr = eNode->first_attribute("name");
		std::string name = nameAttr->value();

		//-----------------------------------------TRANSFORM-----------------------------------------//
		//Posicion
		xml_node<>* tNode = eNode->first_node("transform");
		xml_node<>* posNode = tNode->first_node("position");
		xml_attribute<>* xAttr = posNode->first_attribute("x");
		xml_attribute<>* yAttr = posNode->first_attribute("y");
		xml_attribute<>* zAttr = posNode->first_attribute("z");
		float x = atof(xAttr->value());
		float y = atof(yAttr->value());
		float z = atof(zAttr->value());
		entity->GetTransform()->SetPosition(glt::Vector3(x, y, z));

		//Rotacion
		xml_node<>* rotNode = tNode->first_node("rotation");
		xAttr = rotNode->first_attribute("x");
		yAttr = rotNode->first_attribute("y");
		zAttr = rotNode->first_attribute("z");
		x = atof(xAttr->value());
		y = atof(yAttr->value());
		z = atof(zAttr->value());
		entity->GetTransform()->SetRotation(glt::Vector3(x, y, z));

		//Escala
		xml_node<>* scaleNode = tNode->first_node("scale");
		xAttr = scaleNode->first_attribute("x");
		yAttr = scaleNode->first_attribute("y");
		zAttr = scaleNode->first_attribute("z");
		x = atof(xAttr->value());
		y = atof(yAttr->value());
		z = atof(zAttr->value());
		entity->GetTransform()->SetScale(glt::Vector3(x, y, z));

		//-----------------------------------------OTROS COMPONENTES-----------------------------------------//
		xml_node<>* cameNode = eNode->first_node("camera");
		xml_node<>* lightNode = eNode->first_node("light");
		if (cameNode || lightNode) 
		{
			if (cameNode) 
			{
				//Componente camara
				xml_attribute<>* fovAttr = cameNode->first_attribute("fov");
				float fov = atof(fovAttr->value());
				xml_attribute<>* nearAttr = cameNode->first_attribute("near");
				float near = atof(nearAttr->value());;
				xml_attribute<>* farAttr = cameNode->first_attribute("far");
				float far = atof(farAttr->value());

				float aspecRatio = float(window->GetWidth()) / window->GetHeight();
				std::shared_ptr<CameraComponent> cameraComponent =
					std::make_shared<CameraComponent>(glm::radians(fov), near, far, aspecRatio, GetRenderSystem()->GetRenderer());
				entity->AddComponent("Camera", cameraComponent);
				GetRenderSystem()->SetCameraEntity(entity);
				entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >(name, entity));
			}
			else 
			{
				//Componente luz
				std::shared_ptr<LightComponent> lightComponent = std::make_shared<LightComponent>(GetRenderSystem()->GetRenderer(), entity->GetTransform());
				entity->AddComponent("Light", lightComponent);
				entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >(name, entity));
			}
		}
		//Solo si no son o la camara o la luz pueden tener render o physics
		else 
		{
			//Render
			xml_node<>* rendNode = eNode->first_node("renderable");
			if (rendNode) 
			{
				xml_node<>* colorNode = rendNode->first_node("color");
				xml_attribute<>* rAttr = colorNode->first_attribute("r");
				xml_attribute<>* gAttr = colorNode->first_attribute("g");
				xml_attribute<>* bAttr = colorNode->first_attribute("b");
				float r = atof(rAttr->value());
				float g = atof(gAttr->value());
				float b = atof(bAttr->value());
				glt::Vector3 color(r, g, b);

				std::shared_ptr<RenderableComponent> renderable = std::make_shared<RenderableComponent>(name, color);
				renderable->CubeComponent(GetRenderSystem()->GetRenderer());
				entity->AddComponent("Renderable", renderable);
				GetRenderSystem()->AddRenderableEntity(entity);
			}
			//Fisicas
			xml_node<>* phyNode = eNode->first_node("physics");
			if (phyNode) 
			{
				xml_attribute<>* massAttr = phyNode->first_attribute("mass");
				float mass = atof(massAttr->value());

				std::shared_ptr<PhysicsComponent> physics = std::make_shared<PhysicsComponent>(entity->GetTransform());
				physics->CreateBoxCollider(GetPhysicsSystem()->GetWorld(), entity->GetTransform()->GetScale(), mass);
				
				//Depende de las fisicas
				xml_node<>* playerNode = eNode->first_node("player");
				if (playerNode) 
				{
					xml_attribute<>* speedAttr = playerNode->first_attribute("speed");
					float speed = atof(speedAttr->value());
					std::shared_ptr<PlayerComponent> playerComponent = std::make_shared<PlayerComponent>(physics.get(), speed);
					entity->AddComponent("Player", playerComponent);
					GetMessageDispatcher()->Register("Player", playerComponent);
					//Id para comprobar la colision
					physics->SetCollisionId("Player");
				}
				xml_attribute<>* tagAttr = phyNode->first_attribute("tag");
				if (tagAttr) 
				{
					physics->SetCollisionId(tagAttr->value());
				}

				//Especificado como pared

				entity->AddComponent("Physics", physics);
				GetPhysicsSystem()->AddPhysicEntity(entity);
			}

			entityMap.insert(std::pair<std::string, std::shared_ptr<Entity> >(name, entity));
		}
	}
	return true;
}


void Scene::Run()
{
	kernel.Run();
	GetPhysicsSystem()->EndWorld();
}

std::map<std::string, std::shared_ptr<Entity>> Scene::GetMap()
{
	return entityMap;
}

PhysicsSystem* Scene::GetPhysicsSystem()
{
	PhysicsSystem* ps = dynamic_cast<PhysicsSystem*>(taskMap["PhysicsSystem"].get());
	return ps;
}

RenderSystem* Scene::GetRenderSystem()
{
	RenderSystem* rs = dynamic_cast<RenderSystem*>(taskMap["RenderSystem"].get());
	return rs;
}

MessageDispatcher* Scene::GetMessageDispatcher()
{
	MessageDispatcher* md = dynamic_cast<MessageDispatcher*>(taskMap["MessageDispatcher"].get());
	return md;
}




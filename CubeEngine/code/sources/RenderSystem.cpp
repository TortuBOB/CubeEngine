

// Laura Rosas


#include "../headers//RenderSystem.hpp"
#include "../headers/CameraComponent.hpp"
#include "../headers/LightComponent.hpp"
#include "../headers/RenderableComponent.hpp"


RenderSystem::RenderSystem(Window* wind)
{
	window = wind;

	renderer.reset(new glt::Render_Node);

}

void RenderSystem::Run()
{
	UpdateTransform();
	Render();
}

void RenderSystem::Render()
{
	window->clear();
	renderer->render();
	window->swap_buffers();
}

void RenderSystem::UpdateTransform()
{
	//Actualizar la camara 
	std::shared_ptr<Component> cam = cameraEntity->GetComponent("Camera");
	CameraComponent* camera = dynamic_cast<CameraComponent*>(cam.get());
	camera->UpdatePosition(cameraEntity->GetTransform());

	//Actualizar los objetos de render
	for (size_t i = 0; i < allRenderableEntities.size(); i++)
	{
		std::shared_ptr<Entity> e = allRenderableEntities[i];
		std::shared_ptr<Component> rend = e->GetComponent("Renderable");
		RenderableComponent* renderable = dynamic_cast<RenderableComponent*>(rend.get());
		renderable->UpdateModelTransform(e->GetTransform());
	}
}

void RenderSystem::AddRenderableEntity(std::shared_ptr<Entity> newEntity)
{
	allRenderableEntities.push_back(newEntity);
}

void RenderSystem::SetCameraEntity(std::shared_ptr<Entity> camera)
{
	cameraEntity = camera;
}

void RenderSystem::SetLightEntity(std::shared_ptr<Entity> light)
{
	lightEntity = light;
}




// Laura Rosas


#include "../headers/CameraComponent.hpp"


CameraComponent::CameraComponent()
{
}

CameraComponent::CameraComponent(float fov, float near, float far, float aspect_ratio, std::shared_ptr<glt::Render_Node> renderer)
{
	camera.reset(new glt::Camera(fov, near, far, aspect_ratio));
	
	camera->translate(glt::Vector3(0, 0, 10));

	renderer->add("camera", camera);
}

void CameraComponent::UpdatePosition(TransformComponent* transf)
{
	camera->reset_transformation();
	
	camera->translate(transf->GetPosition());

	camera->rotate_around_x(glm::radians(transf->GetRotation().x));
	camera->rotate_around_y(glm::radians(transf->GetRotation().y));
	camera->rotate_around_z(glm::radians(transf->GetRotation().z));

	camera->scale(1, 1, 1);
}



// Laura Rosas


#include "../headers/LightComponent.hpp"


LightComponent::LightComponent()
{

}

LightComponent::LightComponent(std::shared_ptr<glt::Render_Node> renderer, TransformComponent* entityTranform)
{
	light.reset(new glt::Light);
	light->translate(entityTranform->GetPosition());
	renderer->add("light", light);
}


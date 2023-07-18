

// Laura Rosas


#include"../headers/Entity.hpp"


Entity::Entity()
{
	//Siempre tiene un transform
	std::shared_ptr<TransformComponent> transformComp;
	transformComp.reset(new TransformComponent());
	componentMap.insert(std::pair<std::string, std::shared_ptr<Component>>("Transform", transformComp));
}


void Entity::AddComponent(std::string nameComp, std::shared_ptr<Component> newComp)
{
	componentMap.insert(std::pair<std::string, std::shared_ptr<Component>>(nameComp, newComp));
}

std::shared_ptr<Component> Entity::GetComponent(std::string componentName)
{
	return componentMap[componentName];
}

TransformComponent* Entity::GetTransform()
{
	TransformComponent* transf = dynamic_cast<TransformComponent*>(componentMap["Transform"].get());
	return transf;
}

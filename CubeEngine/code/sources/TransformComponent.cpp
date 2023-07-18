

// Laura Rosas


#include "../headers/TransformComponent.hpp"


TransformComponent::TransformComponent():Component()
{
	position = glt::Vector3(0, 0, 0);
	rotation = glt::Vector3(0, 0, 0);
	compScale = glt::Vector3(1, 1, 1);
}

void TransformComponent::SetPosition(glt::Vector3 pos)
{
	position = pos;
}

glt::Vector3 TransformComponent::GetPosition()
{
	return position;
}

void TransformComponent::SetRotation(glt::Vector3 rot)
{
	rotation = rot;
}

glt::Vector3 TransformComponent::GetRotation()
{
	return rotation;
}

void TransformComponent::SetScale(glt::Vector3 s)
{
	compScale = s;
}

void TransformComponent::SetScale(float s)
{
	compScale = glm::vec3(s, s, s);
}

glt::Vector3 TransformComponent::GetScale()
{
	return compScale;
}

glt::Matrix44 TransformComponent::GetTransformMatrix()
{
	glt::Matrix44 identity(1);
	glt::Matrix44 tempScaling = glm::scale(identity, compScale);
	glt::Matrix44 tempRotX = glm::rotate(identity, rotation.x, glt::Vector3(1.f, 0.f, 0.f));
	glt::Matrix44 tempRotY = glm::rotate(identity, rotation.y, glt::Vector3(0.f, 1.f, 0.f));
	glt::Matrix44 tempRotZ = glm::rotate(identity, rotation.z, glt::Vector3(0.f, 0.f, 1.f));
	glt::Matrix44 tempTranslation = glm::translate(identity, position);
	glt::Matrix44 matrix = tempTranslation * tempScaling * tempRotX * tempRotY * tempRotZ;
	return matrix;
}



// Laura Rosas


#include <iostream>
#include <memory>
#include<Cube.hpp>

#include "../headers/RenderableComponent.hpp" 

using namespace std;
using namespace glt;


RenderableComponent::RenderableComponent():Component()
{
	
}
RenderableComponent::RenderableComponent(std::string name, glt::Vector3 col)
{
	compName = name;
	color = col;

	model.reset(new Model);
	material.reset();
}
void RenderableComponent::CubeComponent(shared_ptr<Render_Node> _scene)
{
	shared_ptr<Drawable> cube_mesh = shared_ptr<Drawable>(new Cube);
	
	material = make_shared <Material>(*Material::default_material());
	material->set("material_color", color);

	model->add(cube_mesh, material);

	_scene->add(compName, model);
}
void RenderableComponent::UpdateModelTransform(TransformComponent* transform)
{
	model->reset_transformation();
	model->set_transformation(transform->GetTransformMatrix());
}





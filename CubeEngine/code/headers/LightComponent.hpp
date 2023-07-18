

/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase es el componente luz que puede tener una entidad
 *
 */


#pragma once

#include <Light.hpp>
#include <Render_Node.hpp>

#include "Component.hpp"
#include "TransformComponent.hpp"


class LightComponent : public Component
{
private:
	/** La luz */
	std::shared_ptr<glt::Light> light;
public:
	/** Constructor vacio */
	LightComponent();

	/**
	 * Constructor de la luz que la coloca en la posición del transform de la entidad
	 *
	 * @param renderer es el render node
	 * @param entityTranform es el transform de la entidad que lo contiene
	 *
	 */
	LightComponent(std::shared_ptr<glt::Render_Node> renderer, TransformComponent* entityTranform);
};


/**
 * @file
 * @author  Laura Rosas Mediavilla
 *
 *
 * @section DESCRIPTION
 *
 * Esta clase es el componete c�mara que puede tener una entidad
 *
 */


#pragma once

#include <Render_Node.hpp>

#include "Component.hpp"
#include "TransformComponent.hpp"


class CameraComponent : public Component
{
private:
	/** La camara */
	std::shared_ptr<glt::Camera> camera;
	
public:
	/** Constructor vacio */
	CameraComponent();

	/**
	 * Constructor de la camara
	 *
	 * @param fov es field of view, en grados
	 * @param near es la min�ma distancia de visi�n
	 * @param far es la m�xima distancia de visi�n
	 * @param aspec_ratio de la pantalla
	 * @param renderer es el render node 
	 *
	 */
	CameraComponent(float fov, float near, float far, float aspect_ratio, std::shared_ptr<glt::Render_Node> renderer);

	/**
	 * Actualiza el transform del objeto c�mara con el componente transform de la entidad
	 *
	 * @param transf es el transform de la entidad
	 *
	 */
	void UpdatePosition(TransformComponent* transf);
};
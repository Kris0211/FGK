#pragma once

#include "Camera.hpp"

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(unsigned int width, unsigned int height, 
		const rtx::Vector3& position, const rtx::Vector3& direction);

	rtx::Ray CastRay(float x, float y) override;
};


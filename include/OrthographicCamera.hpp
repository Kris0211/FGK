#pragma once

#include "Camera.hpp"

class OrthographicCamera : public Camera
{
	float orthogonalWidth;
	float orthogonalHeight;

public:
	OrthographicCamera(unsigned int width, unsigned int height, 
		const rtx::Vector3& position, const rtx::Vector3& direction, 
		float orthoWidth, float orthoHeight);

	rtx::Ray GetRay(unsigned int x, unsigned int y) override;
};


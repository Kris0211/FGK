#pragma once

#include "../RasTerX/include/Ray.hpp"

class Camera
{
protected:
	rtx::Vector3 position;
	rtx::Vector3 direction;

	unsigned int width;
	unsigned int height;

public:
	Camera(unsigned int width, unsigned int height, const rtx::Vector3& position, const rtx::Vector3& direction);

	virtual rtx::Ray CastRay(float x, float y) = 0;
};


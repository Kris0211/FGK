#pragma once

#include "Camera.hpp"

class PerspectiveCamera : public Camera
{
public:
	float fov;
	float nearPlane;
	float farPlane;
	rtx::Vector3 screenPos;

	PerspectiveCamera(const int resX, const int resY, const float nearPlane, const float fov,
		rtx::Vector3 position, rtx::Vector3 target)
		: nearPlane(nearPlane), fov(fov), Camera(resX, resY, position, (target - position).Normal()) 
	{
	}

	rtx::Ray CastRay(float x, float y);
};

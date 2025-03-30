#pragma once

#include "Camera.hpp"

class PerspectiveCamera : public Camera
{
public:
	float fov;
	float planeDist;
	rtx::Vector3 screenPos;

	PerspectiveCamera(const int resX, const int resY, const float farPlane, const float fov,
		rtx::Vector3 position, rtx::Vector3 target = { 0.0f, 0.0f, -1.0f })
		: planeDist(farPlane), fov(fov), Camera(resX, resY, position, target.Normal()) {
	}

	rtx::Ray CastRay(float x, float y);
};

#pragma once

#include "../RasTerX/include/Vector3.hpp"
#include "LightIntensity.hpp"
#include "Renderable.hpp"

#include <memory>


class Light 
{
public:
	rtx::Vector3 position;
	LightIntensity intensity;

	Light(rtx::Vector3 position, LightIntensity intensity) :
		position(position), intensity(intensity) {};

	virtual rtx::Vector3 CalculateLightColor(std::vector<std::shared_ptr<Renderable>> objects,
		rtx::Vector3 intersectionPoint, std::shared_ptr<Renderable> closestObject,
		rtx::Vector3 cameraDir, int n = 0) = 0;

protected:
	rtx::Vector3 ClampColorVector(rtx::Vector3 color)
	{
		return
		{
			rtx::MathUtils::Clamp(color.x, 0.f, 1.f),
			rtx::MathUtils::Clamp(color.y, 0.f, 1.f),
			rtx::MathUtils::Clamp(color.z, 0.f, 1.f),
		};
	}
};

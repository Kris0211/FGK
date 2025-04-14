#pragma once
#include "Light.hpp"

class PointLight : public Light {
public:
	rtx::Vector3 position;

	float constAtten;
	float linearAtten;
	float quadAtten;

	PointLight(rtx::Vector3 position, LightIntensity lightIntensity, const float constAtten, 
		const float linearAtten, const float quadAtten) : 
	Light(position, lightIntensity), constAtten(constAtten), 
	linearAtten(linearAtten), quadAtten(quadAtten) {}

	rtx::Vector3 CalculateLightColor(std::vector<std::shared_ptr<Renderable>> renderables,
		rtx::Vector3 intersectionPoint, std::shared_ptr<Renderable> closestRenderable,
		rtx::Vector3 cameraDir, int n = 0) override;
};

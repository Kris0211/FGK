#pragma once
#include <vector>
#include "Renderable.hpp"
#include "Light.hpp"
#include "Camera.hpp"

class Scene
{
public:
	Scene(int reflectionLimit = 1);

	std::vector<std::shared_ptr<Renderable>> renderables;
	std::vector<std::shared_ptr<Light>> lights;

	int reflectionLimit;

	rtx::Vector3 CalculateLighting(const rtx::Vector3& intersection, const std::shared_ptr<Renderable> closestRenderable, 
		const rtx::Vector3& cameraDirection, const int n = 0);


	void CheckIntersections(const rtx::Ray ray, rtx::Vector3& intersection, std::shared_ptr<Renderable>& closestRenderable, int& foundID);

	void AddRenderable(const std::shared_ptr<Renderable>& renderable);
	void AddLight(const std::shared_ptr<Light>& light);
};
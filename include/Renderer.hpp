#pragma once
#include "Buffer.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class Renderer
{
private:
	std::unique_ptr<Buffer> colorBuffer;
	
	std::vector<std::shared_ptr<Renderable>> renderables;
	std::vector<std::shared_ptr<Light>> lights;

	unsigned int samplesPerPixel;
	unsigned int maxBounces;
	unsigned int tilesPerRow;

	std::shared_ptr<Camera> camera;

public:
	Renderer(unsigned int width, unsigned int height, unsigned int samplesPerPixel, 
		unsigned int maxBounces, unsigned int tilesPerRow);
	~Renderer();

	void AddRenderable(const std::shared_ptr<Renderable>& renderable);
	void AddLight(const std::shared_ptr<Light>& light);

	void Render(const std::shared_ptr<Camera> camera);
	void Save(const std::string& path) const;

	unsigned int GetSamplesPerPixel() const { return samplesPerPixel; }
	unsigned int GetMaxBounces() const { return maxBounces; }
	unsigned int GetTilesPerRow() const { return tilesPerRow; }

private:
	rtx::Vector3 Sampling(const std::shared_ptr<Camera> camera, const int x, const int y,
		const int maxSteps, const float xCenter, const float yCenter, const float offset);
	rtx::Vector3 GetColor(const std::shared_ptr<Camera> camera, const float x, const float y);
	rtx::Vector3 CalculateLighting(const rtx::Vector3& intersectionPoint,
		const std::shared_ptr<Renderable>& closestObject, const rtx::Vector3& cameraDir, const int n = 0);
};

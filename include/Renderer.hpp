#pragma once
#include "Buffer.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Scene.hpp"

class Renderer
{
private:
	std::unique_ptr<Buffer> colorBuffer;

	unsigned int samplesPerPixel;
	unsigned int tilesPerRow;

public:
	Renderer(unsigned int width, unsigned int height, unsigned int samplesPerPixel,
		unsigned int tilesPerRow);
	~Renderer();

	void Render(const std::shared_ptr<Camera> camera, const std::shared_ptr<Scene> scene);
	void Save(const std::string& path) const;

	unsigned int GetSamplesPerPixel() const { return samplesPerPixel; }
	unsigned int GetTilesPerRow() const { return tilesPerRow; }

private:
	rtx::Vector3 Sampling(const std::shared_ptr<Camera> camera, const std::shared_ptr<Scene> scene, const int x, const int y,
		const int maxSteps, const float xCenter, const float yCenter, const float offset);
	rtx::Vector3 GetColor(const std::shared_ptr<Camera> camera, const std::shared_ptr<Scene> scene, const float x, const float y);
};

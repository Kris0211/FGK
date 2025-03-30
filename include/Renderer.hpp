#pragma once
#include "Buffer.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"

class Renderer
{
private:
	std::unique_ptr<Buffer> colorBuffer;
	
	std::vector<std::shared_ptr<Renderable>> renderables;

	unsigned int samplesPerPixel;
	unsigned int maxBounces;
	unsigned int tilesPerRow;

	std::shared_ptr<Camera> camera;

public:
	Renderer(unsigned int width, unsigned int height, unsigned int samplesPerPixel, unsigned int maxBounces, unsigned int tilesPerRow);
	~Renderer();

	void AddRenderable(const std::shared_ptr<Renderable>& renderable);

	void Render(const std::shared_ptr<Camera> camera);
	void Save(const std::string& path) const;

	unsigned int GetSamplesPerPixel() const { return samplesPerPixel; }
	unsigned int GetMaxBounces() const { return maxBounces; }
	unsigned int GetTilesPerRow() const { return tilesPerRow; }
};


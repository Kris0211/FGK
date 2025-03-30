#include "../include/Renderer.hpp"
#include "../include/TGA.hpp"

Renderer::Renderer(unsigned int width, unsigned int height, unsigned int samplesPerPixel, unsigned int maxBounces, unsigned int tilesPerRow) 
	: samplesPerPixel(samplesPerPixel), maxBounces(maxBounces), tilesPerRow(tilesPerRow)
{
	colorBuffer = std::make_unique<Buffer>(width, height);
}

Renderer::~Renderer()
{
}

void Renderer::AddRenderable(const std::shared_ptr<Renderable>& renderable)
{
	renderables.push_back(renderable);
}

void Renderer::Render(const std::shared_ptr<Camera> camera)
{
	colorBuffer->SetBufferColorFill(0xFF000000);

	for (int x = 0; x < colorBuffer->GetWidth(); ++x)
	{
		for (int y = 0; y < colorBuffer->GetHeight(); ++y)
		{
			bool foundHit = false;

			rtx::Vector3 hit;
			rtx::Vector3 outHit(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());

			Material material;
			Material outMaterial;

			rtx::Ray ray = camera->GetRay(x, y);

			for (const std::shared_ptr<Renderable>& renderable : renderables)
			{
				if (renderable->Trace(ray, hit, material) && ray.origin.Dot(hit) < ray.origin.Dot(outHit))
				{
					foundHit = true;
					outHit = hit;
					outMaterial = material;
				}
			}

			if (foundHit)
			{
				colorBuffer->SetPixel(x, y, outMaterial.GetColor());
			}
		}
	}
}

void Renderer::Save(const std::string& path) const
{
	TGA::Save(path, colorBuffer->GetColorBuffer(), colorBuffer->GetWidth(), colorBuffer->GetHeight());
}

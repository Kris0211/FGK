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
			rtx::Vector3 sampledColor = Sampling(camera, x, y, 4, 0.0f, 0.0f, 0.5f);
			Color pixelColor = Color(sampledColor, 1.f);
			colorBuffer->SetPixel(x, y, pixelColor.ToHex());
		}
	}
}

void Renderer::Save(const std::string& path) const
{
	TGA::Save(path, colorBuffer->GetColorBuffer(), colorBuffer->GetWidth(), colorBuffer->GetHeight());
}

rtx::Vector3 Renderer::Sampling(const std::shared_ptr<Camera> camera, const int x, const int y,
	const int maxSteps, const float xCenter, const float yCenter, const float offset)
{
	rtx::Vector3 color = rtx::Vector3::Zero(); // black
	rtx::Vector3 centerColor = GetColor(camera, x + xCenter, y + yCenter);

	std::vector<rtx::Vector3> tmpColors = {
		GetColor(camera, x + xCenter - offset, y + yCenter - offset),
		GetColor(camera, x + xCenter + offset, y + yCenter - offset),
		GetColor(camera, x + xCenter - offset, y + yCenter + offset),
		GetColor(camera, x + xCenter + offset, y + yCenter + offset),
	};

	if (maxSteps > 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((tmpColors[i] - centerColor).Length() > 0.4f)
			{
				const float newOffset = offset * 0.5f;
				const float newX = xCenter + ((i % 2 == 0) ? -newOffset : newOffset);
				const float newY = yCenter + ((i < 2) ? -newOffset : newOffset);

				tmpColors[i] = Sampling(camera, x, y, maxSteps - 1, newX, newY, newOffset);
			}
			else
			{
				tmpColors[i] = (tmpColors[i] + centerColor) * 0.5f;
			}
		}

		for (const auto& c : tmpColors)
		{
			color += c;
		}
	}

	return color / static_cast<float>(tmpColors.size());
}

rtx::Vector3 Renderer::GetColor(const std::shared_ptr<Camera> camera, const float x, const float y)
{
	rtx::Ray ray = camera->CastRay(x, y);
	
	rtx::Vector3 hit;
	rtx::Vector3 closestHit(FLT_MAX, FLT_MAX, FLT_MAX);

	Material material;
	Material closestMaterial;

	Color hitColor = Color(0xFF000000);

	bool foundHit = false;

	for (const std::shared_ptr<Renderable>& renderable : renderables)
	{
		if (renderable->Trace(ray, hit, material))
		{
			if ((hit - ray.origin).Length() < (closestHit - ray.origin).Length())
			{
				foundHit = true;
				closestHit = hit;
				closestMaterial = material;
			}
		}
	}

	if (foundHit)
	{
		hitColor = closestMaterial.GetColor();
	}
	return hitColor.ToVector();
}

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

void Renderer::AddLight(const std::shared_ptr<Light>& light)
{
	lights.push_back(light);
}

void Renderer::Render(const std::shared_ptr<Camera> camera)
{
	colorBuffer->SetBufferColorFill(0xFF000000);

	for (unsigned int x = 0; x < colorBuffer->GetWidth(); ++x)
	{
		for (unsigned int y = 0; y < colorBuffer->GetHeight(); ++y)
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

	std::shared_ptr<Renderable> closestRenderable;

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
				closestRenderable = renderable;
			}
		}
	}

	if (foundHit)
	{
		auto viewDir = (camera->GetPosition() - closestHit).Normal();
		auto colorVec = CalculateLighting(closestHit, closestRenderable, viewDir);
		hitColor = Color(colorVec);
	}
	return hitColor.ToVector();
}

rtx::Vector3 Renderer::CalculateLighting(const rtx::Vector3& intersectionPoint, 
	const std::shared_ptr<Renderable>& closestObject, const rtx::Vector3& cameraDir, const int n)
{
	if (lights.empty())
	{
		return rtx::Vector3::Zero();
	}

	rtx::Vector3 finalColor = rtx::Vector3::Zero();

	for (const auto& light : lights)
	{
		finalColor += light->CalculateLightColor(renderables, intersectionPoint, closestObject, cameraDir, n);
	}

	finalColor /= static_cast<float>(lights.size());

	return finalColor;
}

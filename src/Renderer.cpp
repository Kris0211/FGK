#include "../include/Renderer.hpp"
#include "../include/TGA.hpp"

Renderer::Renderer(unsigned int width, unsigned int height, unsigned int samplesPerPixel, unsigned int tilesPerRow)
	: samplesPerPixel(samplesPerPixel), tilesPerRow(tilesPerRow)
{
	colorBuffer = std::make_unique<Buffer>(width, height);
}

Renderer::~Renderer()
{
}

void Renderer::Render(const std::shared_ptr<Camera> camera, const std::shared_ptr<Scene> scene)
{
	colorBuffer->SetBufferColorFill(0xFF000000);

	for (unsigned int x = 0; x < colorBuffer->GetWidth(); ++x)
	{
		for (unsigned int y = 0; y < colorBuffer->GetHeight(); ++y)
		{
			rtx::Vector3 sampledColor = Sampling(camera, scene, x, y, 4, 0.0f, 0.0f, 0.5f);
			Color pixelColor = Color(sampledColor, 1.f);
			colorBuffer->SetPixel(x, y, pixelColor.ToHex());
		}
	}
}

void Renderer::Save(const std::string& path) const
{
	TGA::Save(path, colorBuffer->GetColorBuffer(), colorBuffer->GetWidth(), colorBuffer->GetHeight());
}

rtx::Vector3 Renderer::Sampling(const std::shared_ptr<Camera> camera, const std::shared_ptr<Scene> scene, const int x, const int y,
	const int maxSteps, const float xCenter, const float yCenter, const float offset)
{
	rtx::Vector3 color = rtx::Vector3::Zero(); // black
	rtx::Vector3 centerColor = GetColor(camera, scene, x + xCenter, y + yCenter);

	std::vector<rtx::Vector3> tmpColors = {
		GetColor(camera, scene, x + xCenter - offset, y + yCenter - offset),
		GetColor(camera, scene, x + xCenter + offset, y + yCenter - offset),
		GetColor(camera, scene, x + xCenter - offset, y + yCenter + offset),
		GetColor(camera, scene, x + xCenter + offset, y + yCenter + offset),
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

				tmpColors[i] = Sampling(camera, scene, x, y, maxSteps - 1, newX, newY, newOffset);
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

rtx::Vector3 Renderer::GetColor(const std::shared_ptr<Camera> camera, const std::shared_ptr<Scene> scene, const float x, const float y)
{
	rtx::Ray ray = camera->CastRay(x, y);
	
	rtx::Vector3 closestHit(FLT_MAX, FLT_MAX, FLT_MAX);

	std::shared_ptr<Renderable> closestRenderable;

	Color hitColor = Color(0xFF000000);

	int foundID = -1;
	
	scene->CheckIntersections(ray, closestHit, closestRenderable, foundID);

	if (foundID >= 0)
	{
		auto viewDir = (camera->GetPosition() - closestHit).Normal();
		auto colorVec = scene->CalculateLighting(closestHit, closestRenderable, viewDir, foundID);
		hitColor = Color(colorVec);
	}

	return hitColor.ToVector();
}

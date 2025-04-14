#include "..\include\Scene.hpp"

Scene::Scene(int reflectionLimit) : reflectionLimit(reflectionLimit)
{
}

rtx::Vector3 Scene::CalculateLighting(const rtx::Vector3& intersection, const std::shared_ptr<Renderable> closestRenderable, const rtx::Vector3& cameraDirection, const int n)
{
	if (lights.empty())
	{
		return closestRenderable->GetMaterial().GetColor().ToVector();
	}

	rtx::Vector3 finalColor = rtx::Vector3::Zero();

	for (const auto& light : lights)
	{
		finalColor += light->CalculateLightColor(renderables, intersection, closestRenderable, cameraDirection, n);
	}

	finalColor /= static_cast<float>(lights.size());

	return finalColor;
}

void Scene::CheckIntersections(const rtx::Ray ray, rtx::Vector3& intersection, std::shared_ptr<Renderable>& closestRenderable, int& foundID)
{
	rtx::Vector3 hit;
	Material material;

	bool found = false;
	int n = foundID;
	foundID = -1;

	for (const std::shared_ptr<Renderable>& renderable : renderables)
	{
		int id = std::find(renderables.begin(), renderables.end(), renderable) - renderables.begin();

		if (renderable->Trace(ray, hit, material))
		{
			if ((hit - ray.origin).Length() < (intersection - ray.origin).Length() && foundID != id && n != id)
			{
				found = true;
				foundID = id;
				intersection = hit;
				closestRenderable = renderable;
			}
		}
	}

	if (found && reflectionLimit > 0)
	{
		for (int i = 0; i < reflectionLimit; ++i)
		{
			rtx::Ray reflectionRay;

			if (closestRenderable->GetMaterial().refract > 0.001f)
			{
				reflectionRay = rtx::Ray(intersection, rtx::MathUtils::Refract(ray.direction.Normal(), intersection, closestRenderable->GetMaterial().refract));
			}
			else if (closestRenderable->GetMaterial().reflect > 0.001f)
			{
				reflectionRay = rtx::Ray(intersection, rtx::MathUtils::Reflect(ray.direction, intersection));
			}
			else
			{
				return;
			}

			CheckIntersections(reflectionRay, intersection, closestRenderable, foundID);
		}
	}
}

void Scene::AddRenderable(const std::shared_ptr<Renderable>& renderable)
{
	renderables.push_back(renderable);
}

void Scene::AddLight(const std::shared_ptr<Light>& light)
{
	lights.push_back(light);
}
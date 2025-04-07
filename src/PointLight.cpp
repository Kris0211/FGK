#include "../include/PointLight.hpp"

rtx::Vector3 PointLight::CalculateLightColor(std::vector<std::shared_ptr<Renderable>> objects,
	rtx::Vector3 intersectionPoint, std::shared_ptr<Renderable> closestObject, rtx::Vector3 cameraDir, int n)
{
	bool isInShadow = false;
	rtx::Ray ray(position, (intersectionPoint - position).Normal(), FLT_MAX);

	float closestDist = 1000;
	int closestNumber = n;
	rtx::Vector3 distance = rtx::Vector3(-1000, -1000, -1000);

	rtx::Vector3 intersection;
	rtx::Vector3 closestIntersection;
	Material material;

	for (int i = 0; i < objects.size(); i++)
	{
		std::shared_ptr<Renderable> obj = objects[i];
		if (obj->Trace(ray, intersection, material))
		{
			float distance = (ray.origin - intersection).Length();
			if (distance < closestDist)
			{
				closestDist = distance;
				closestNumber = i;
				closestIntersection = intersection;
			}
		}
	}

	float difference = fabs((position - intersectionPoint).Length() - (position - closestIntersection).Length());

	if (closestNumber != n || (closestNumber == n && difference > 0.001f))
	{
		isInShadow = true;
	}

	rtx::Vector3 baseColor = closestObject->GetMaterial().GetColor().ToVector();
	rtx::Vector3 ambient = baseColor * 0.2f;

	ambient.x *= intensity.r;
	ambient.y *= intensity.g;
	ambient.z *= intensity.b;

	if (isInShadow)
	{
		return ClampColorVector(ambient);
	}

	// Phong
	rtx::Vector3 lightDir = (position - intersectionPoint).Normal();
	rtx::Vector3 normal = (intersectionPoint - closestObject->GetPosition()).Normal();

	rtx::Vector3 R = lightDir - (normal * normal.Dot(lightDir) * 2.f);
	const float ss = -cameraDir.Dot(R);

	float spec = -ss > 0 ? pow(ss, closestObject->GetMaterial().specular) : 0.f;
	spec *= closestObject->GetMaterial().specularCoeff;

	float shade = normal.Dot(lightDir);
	const float atten = 1.f / (constAtten + linearAtten * closestDist + quadAtten * (closestDist * closestDist));
	shade = rtx::MathUtils::Clamp(shade * atten, 0.2f, 1.0f);
	baseColor.x *= shade * intensity.r;
	baseColor.y *= shade * intensity.g;
	baseColor.z *= shade * intensity.b;

	rtx::Vector3 specular = baseColor * spec;
	specular.x *= intensity.r;
	specular.y *= intensity.g;
	specular.z *= intensity.b;

	baseColor += specular;

	return ClampColorVector(baseColor);
}

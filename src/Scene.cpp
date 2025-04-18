#include "..\include\Scene.hpp"

Scene::Scene(unsigned int reflectionLimit) 
    : reflectionLimit(reflectionLimit) {}

rtx::Vector3 Scene::CalculateLighting(const rtx::Ray& ray, const rtx::Vector3& intersection,
    const std::shared_ptr<Renderable> closestRenderable, const rtx::Vector3& cameraDirection,
    const int n, int depth)
{
    if (depth >= reflectionLimit) 
    {
        return rtx::Vector3::Zero();
    }

    rtx::Vector3 directLighting = rtx::Vector3::Zero();
    for (const auto& light : lights) 
    {
        directLighting += light->CalculateLightColor(renderables, intersection, closestRenderable, cameraDirection, n);
    }

    if (!lights.empty()) 
    {
        directLighting /= static_cast<float>(lights.size());
    }

    rtx::Vector3 reflectionColor = rtx::Vector3::Zero();
    float reflectAmount = closestRenderable->GetMaterial().reflect;

    if (reflectAmount > 0.001f) 
    {
        rtx::Vector3 normal = (intersection - closestRenderable->GetPosition()).Normal();
        rtx::Vector3 reflectDir = rtx::MathUtils::Reflect(ray.direction, normal);
        rtx::Ray reflectionRay(intersection + reflectDir * 0.001f, reflectDir);

        rtx::Vector3 reflHit(FLT_MAX, FLT_MAX, FLT_MAX);
        std::shared_ptr<Renderable> reflRenderable;
        int reflID = -1;

        CheckIntersections(reflectionRay, reflHit, reflRenderable, reflID);

        if (reflID >= 0) 
        {
            rtx::Vector3 reflViewDir = -reflectionRay.direction;
            reflectionColor = CalculateLighting(
                reflectionRay, reflHit, reflRenderable, reflViewDir, reflID, depth + 1);
        }
    }

    rtx::Vector3 refractionColor = rtx::Vector3::Zero();
    float refractAmount = closestRenderable->GetMaterial().refract;

    if (refractAmount > 0.001f) 
    {
        rtx::Vector3 normal = (intersection - closestRenderable->GetPosition()).Normal();
        rtx::Vector3 refractDir = rtx::MathUtils::Refract(ray.direction.Normal(), normal, refractAmount);
        rtx::Ray refractionRay(intersection + refractDir * 0.001f, refractDir);

        rtx::Vector3 refrHit(FLT_MAX, FLT_MAX, FLT_MAX);
        std::shared_ptr<Renderable> refrRenderable;
        int refrID = -1;

        CheckIntersections(refractionRay, refrHit, refrRenderable, refrID);

        if (refrID >= 0) {
            rtx::Vector3 refrViewDir = -refractionRay.direction;
            refractionColor = CalculateLighting(
                refractionRay, refrHit, refrRenderable, refrViewDir, refrID, depth + 1);
        }
    }

    float remainingIntensity = 1.0f - std::min(1.0f, std::max(0.0f, reflectAmount + refractAmount));
    return directLighting * remainingIntensity 
        + reflectionColor * std::min(1.0f, std::max(0.0f, reflectAmount)) 
        + refractionColor * std::min(1.0f, std::max(0.0f, refractAmount));
}

void Scene::CheckIntersections(const rtx::Ray ray, rtx::Vector3& intersection,
    std::shared_ptr<Renderable>& closestRenderable, int& foundID)
{
    rtx::Vector3 hit;
    Material material;
    float closestDistance = FLT_MAX;

    foundID = -1;

    for (int id = 0; id < renderables.size(); id++) {
        auto& renderable = renderables[id];

        if (renderable->Trace(ray, hit, material)) {
            float distance = (hit - ray.origin).Length();
            if (distance < closestDistance) {
                closestDistance = distance;
                foundID = id;
                intersection = hit;
                closestRenderable = renderable;
            }
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

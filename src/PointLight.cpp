#include "../include/PointLight.hpp"

rtx::Vector3 PointLight::CalculateLightColor(std::vector<std::shared_ptr<Renderable>> renderables,
    rtx::Vector3 intersectionPoint, std::shared_ptr<Renderable> closestRenderable, rtx::Vector3 cameraDir, int n)
{
    rtx::Vector3 baseColor = closestRenderable->GetMaterial().GetColor().ToVector();
    const float specIntensity = closestRenderable->GetMaterial().specular;
    const float specCoeff = closestRenderable->GetMaterial().specularCoeff;

    rtx::Vector3 lightColorVec(intensity.r, intensity.g, intensity.b);
    rtx::Vector3 ambient = baseColor * 0.2f * lightColorVec;

    rtx::Vector3 normal = closestRenderable->GetNormalAt(intersectionPoint);

    const float shadowBias = 0.001f;
    rtx::Vector3 offsetIntersection = intersectionPoint + normal * shadowBias;

    rtx::Vector3 dirToLight = (position - offsetIntersection).Normal();
    const float distToLight = (position - offsetIntersection).Length();

    rtx::Ray shadowRay(offsetIntersection, dirToLight, distToLight);

    bool isInShadow = false;
    for (int i = 0; i < renderables.size(); i++)
    {
        if (i == n)
            continue;

        rtx::Vector3 shadowIntersection;
        Material tempMat;
        if (renderables[i]->Trace(shadowRay, shadowIntersection, tempMat))
        {
            const float refractAmount = renderables[i]->GetMaterial().refract;

            if (std::abs(refractAmount - 1.0f) < 0.001f)
                continue;

            if ((shadowIntersection - offsetIntersection).Length() < distToLight - shadowBias)
            {
                isInShadow = true;
                break;
            }
        }
    }

    //if (isInShadow) return Color(Color::RED).ToVector();
    //else return Color(Color::GREEN).ToVector();

    if (isInShadow)
        return ClampColorVector(ambient);

    rtx::Vector3 lightDir = dirToLight;
    float lightDist = distToLight;

    float attenuation = 1.0f / (constAtten + linearAtten * lightDist + quadAtten * lightDist * lightDist);

    float diffuseFactor = std::abs(normal.Dot(lightDir));
    rtx::Vector3 diffuse = baseColor * diffuseFactor * lightColorVec;

    rtx::Vector3 reflectDir = normal * 2.f * normal.Dot(lightDir) - lightDir;
    reflectDir = reflectDir.Normal();

    rtx::Vector3 viewDir = -cameraDir.Normal();

    float RdotV = std::abs(reflectDir.Dot(viewDir));
    float specFactor = pow(RdotV, specCoeff) * specIntensity;

    rtx::Vector3 specular = rtx::Vector3::One() * specFactor * lightColorVec;

    rtx::Vector3 finalColor = ambient + (diffuse + specular) * attenuation;
    return ClampColorVector(finalColor);
}

#include "../include/PointLight.hpp"

rtx::Vector3 PointLight::CalculateLightColor(std::vector<std::shared_ptr<Renderable>> renderables,
	rtx::Vector3 intersectionPoint, std::shared_ptr<Renderable> closestRenderable, rtx::Vector3 cameraDir, int n)
{
    rtx::Vector3 baseColor = closestRenderable->GetMaterial().GetColor().ToVector();
    float specCoeff = closestRenderable->GetMaterial().specularCoeff;
    float specIntensity = closestRenderable->GetMaterial().specular;

    rtx::Vector3 lightColorVec(intensity.r, intensity.g, intensity.b);
    rtx::Vector3 ambient = baseColor * 0.2f * lightColorVec;

    bool isInShadow = false;

    rtx::Vector3 offsetIntersection = intersectionPoint +
        (intersectionPoint - closestRenderable->GetPosition()).Normal() * 0.001f;
    rtx::Ray shadowRay(offsetIntersection, (position - offsetIntersection).Normal(),
        (position - offsetIntersection).Length());

    for (int i = 0; i < renderables.size(); i++) 
    {
        if (i == n) 
            continue;

        rtx::Vector3 shadowIntersection;
        Material tempMat;
        if (renderables[i]->Trace(shadowRay, shadowIntersection, tempMat)) 
        {
            isInShadow = true;
            break;
        }
    }

    if (isInShadow) 
    {
        return ClampColorVector(ambient);
    }

    rtx::Vector3 lightDir = (position - intersectionPoint).Normal();
    const float lightDist = (position - intersectionPoint).Length();
    rtx::Vector3 normal = (intersectionPoint - closestRenderable->GetPosition()).Normal();
    rtx::Vector3 viewDir = cameraDir.Normal();

    float attenuation = 1.0f / (constAtten + linearAtten * lightDist + quadAtten * lightDist * lightDist);

    float diffuseFactor = std::max(normal.Dot(lightDir), 0.0f);
    rtx::Vector3 diffuse = baseColor * diffuseFactor * lightColorVec;

    rtx::Vector3 reflectDir = normal * 2.0f * normal.Dot(lightDir) - lightDir;
    reflectDir = reflectDir.Normal();

    float RdotV = std::max(reflectDir.Dot(viewDir), 0.0f);
    float specFactor = pow(RdotV, closestRenderable->GetMaterial().specularCoeff) * closestRenderable->GetMaterial().specular;

    rtx::Vector3 specular = rtx::Vector3(1.0f, 1.0f, 1.0f) * specFactor * lightColorVec;

    rtx::Vector3 finalColor = ambient + (diffuse + specular) * attenuation;
    return ClampColorVector(finalColor);
}

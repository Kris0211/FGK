#pragma once

#include "Material.hpp"
#include "../RasTerX/include/Sphere.hpp"

class Renderable
{
private:
	Material material;

public:
	explicit Renderable(const Material& material);

	Material& GetMaterial() { return material; };

	virtual bool Trace(const rtx::Ray& ray, rtx::Vector3& ref_RayHit, Material& ref_Material) = 0;
};

class SphereRenderable : public Renderable
{
private:
	rtx::Sphere sphere;

public:
	SphereRenderable(const Material& material, const rtx::Sphere sphere);

	bool Trace(const rtx::Ray& ray, rtx::Vector3& ref_RayHit, Material& ref_Material) override;
};

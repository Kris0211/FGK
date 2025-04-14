#pragma once

#include "Material.hpp"
#include "../RasTerX/include/Sphere.hpp"
#include "../RasTerX/include/Plane.hpp"

class Renderable
{
private:
	Material material;

public:
	explicit Renderable(const Material& material);

	Material& GetMaterial() { return material; };

	virtual bool Trace(const rtx::Ray& ray, rtx::Vector3& ref_RayHit, Material& ref_Material) = 0;
	virtual rtx::Vector3 GetPosition() const = 0;
};

class SphereRenderable : public Renderable
{
private:
	rtx::Sphere sphere;

public:
	SphereRenderable(const Material& material, const rtx::Sphere sphere);

	bool Trace(const rtx::Ray& ray, rtx::Vector3& ref_RayHit, Material& ref_Material) override;
	rtx::Vector3 GetPosition() const { return sphere.center; }
};

class PlaneRenderable : public Renderable
{
private:
	rtx::Plane plane;

public:
	PlaneRenderable(const Material& material, const rtx::Plane plane);

	bool Trace(const rtx::Ray& ray, rtx::Vector3& ref_RayHit, Material& ref_Material) override;
	rtx::Vector3 GetPosition() const { return plane.p; }
};
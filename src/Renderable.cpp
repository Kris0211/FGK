#include "../include/Renderable.hpp"

Renderable::Renderable(const Material& material) : material(material)
{
}

SphereRenderable::SphereRenderable(const Material& material, const rtx::Sphere sphere) : Renderable(material), sphere(sphere)
{}

bool SphereRenderable::Trace(const rtx::Ray& ray, rtx::Vector3& ref_RayHit, Material& ref_Material)
{
	rtx::Vector3 rayHit;

	bool check = sphere.Intersects(ray, rayHit);

	if (check)
	{
		ref_RayHit = rayHit;
		ref_Material = GetMaterial();
	}

	return check;
}

PlaneRenderable::PlaneRenderable(const Material& material, const rtx::Plane plane) 
	: Renderable(material), plane(plane)
{}

bool PlaneRenderable::Trace(const rtx::Ray& ray, rtx::Vector3& ref_RayHit, Material& ref_Material)
{
	rtx::Vector3 rayHit;

	bool check = plane.Intersects(ray, rayHit);

	if (check)
	{
		ref_RayHit = rayHit;
		ref_Material = GetMaterial();
	}

	return check;
}

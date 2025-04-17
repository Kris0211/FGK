#include "../include/PerspectiveCamera.hpp"
#include "../RasTerX/include/MathUtils.hpp"

rtx::Ray PerspectiveCamera::CastRay(float x, float y)
{
	const float aspect = width / height;

	const float fovRad = fov * PI / 180.0f;
	const float hh = tanf(fovRad / 2.0f) * nearPlane;
	const float hw = aspect * hh;

	const float u = (2.f * (x + 0.5f) / width - 1.f) * hw;
	const float v = (1.f - 2.f * (y + 0.5f) / height) * hh;

	rtx::Vector3 w = -direction.Normal();
	rtx::Vector3 up = rtx::Vector3::Up();
	rtx::Vector3 uVec = up.Cross(w).Normal();
	rtx::Vector3 vVec = w.Cross(uVec).Normal();

	rtx::Vector3 dir = (uVec * u + vVec * v - w * nearPlane).Normal();

	return { position, dir , FLT_MAX};
}

#include "../include/PerspectiveCamera.hpp"
#include "../RasTerX/include/MathUtils.hpp"

rtx::Ray PerspectiveCamera::CastRay(float x, float y)
{
	const float aspect = width / height;

	const float hh = tan((fov * PI / 360.f) / 2.f) * planeDist;
	const float hw = aspect * hh;

	const float l = -hw;
	const float r = hw;
	const float b = -hh;
	const float t = hh;

	const float u = l + ((r - l) * (x + 0.5f)) / width;
	const float v = b + ((t - b) * (y + 0.5f)) / height;

	rtx::Vector3 gaze = (direction - position).Normal();
	rtx::Vector3 w = -gaze.Normal();

	rtx::Vector3 camUp = rtx::Vector3(0.f, -1.f, 0.f);
	rtx::Vector3 uVec = camUp.Cross(w).Normal();
	rtx::Vector3 vVec = w.Cross(uVec).Normal();

	rtx::Vector3 dir = (uVec * u + vVec * v + w * -planeDist).Normal();

	return { position, dir , FLT_MAX};
}

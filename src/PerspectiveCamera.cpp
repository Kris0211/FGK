#include "../include/PerspectiveCamera.hpp"
#include "../RasTerX/include/MathUtils.hpp"

rtx::Ray PerspectiveCamera::CastRay(float x, float y)
{
	float aspect = width / height;

	float hh = tan((fov * PI / 360.f) / 2.f) * planeDist;
	float hw = aspect * hh;

	float l = -hw; 
	float r = hw;
	float b = -hh; 
	float t = hh;

	float u = l + ((r - l) * (x + 0.5f)) / width;
	float v = b + ((t - b) * (y + 0.5f)) / height;

	rtx::Vector3 gaze = (direction - position).Normal();
	rtx::Vector3 w = -gaze.Normal();

	rtx::Vector3 camUp = rtx::Vector3(0.f, -1.f, 0.f);
	rtx::Vector3 uVec = camUp.Cross(w).Normal();
	rtx::Vector3 vVec = w.Cross(uVec).Normal();

	rtx::Vector3 dir = (uVec * u + vVec * v + w * -planeDist).Normal();

	return { position, dir , FLT_MAX};
}

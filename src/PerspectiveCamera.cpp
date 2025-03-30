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

	rtx::Vector3 gaze = direction - position;

	rtx::Vector3 w = -gaze;
	w = w.Normal();

	rtx::Vector3 uVec = rtx::Vector3::Up().Cross(w);
	uVec = uVec.Normal();

	rtx::Vector3 vVec = w.Cross(uVec);
	vVec = vVec.Normal();

	rtx::Vector3 e = position;

	rtx::Vector3 o = e;
	rtx::Vector3 d = w * -(planeDist) + uVec * u + vVec * v;

	return { o, d , FLT_MAX };
}

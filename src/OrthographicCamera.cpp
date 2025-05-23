#include "../include/OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(unsigned int width, unsigned int height, 
	const rtx::Vector3& position, const rtx::Vector3& direction) 
	: Camera(width, height, position, direction)
{
}

rtx::Ray OrthographicCamera::CastRay(float x, float y)
{
	const float pixelWidth = 2.f / width;
	const float pixelHeight = 2.f / height;

	float xPixelCenter = -1.f + (x + 0.5f) * pixelWidth;
	float yPixelCenter = 1.f - (y + 0.5f) * pixelHeight;

	rtx::Vector3 offset(xPixelCenter, yPixelCenter, 0.f);

	return { position + offset, direction.Normal(), FLT_MAX };
}

#include "../include/OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(unsigned int width, unsigned int height, 
	const rtx::Vector3& position, const rtx::Vector3& direction, 
	float orthoWidth, float orthoHeight) 
	: Camera(width, height, position, direction), orthogonalWidth(orthoWidth), orthogonalHeight(orthoHeight)
{
}

rtx::Ray OrthographicCamera::GetRay(unsigned int x, unsigned int y)
{
	const float xStep = orthogonalWidth / width;
	const float yStep = orthogonalHeight / height;

	const rtx::Vector3 right = -direction.Cross({0.f, 1.f, 0.f}).Normal();
	const rtx::Vector3 up = -direction.Cross(right).Normal();

	const rtx::Vector3 left = -right;
	const rtx::Vector3 down = -up;

	rtx::Vector3 start = position + (left * (orthogonalWidth * 0.5f)) + (up * (orthogonalHeight * 0.5f));

	// Jitter?

	rtx::Vector3 offset = (right * xStep * x) + (down * yStep * y);

	return {direction, start + offset};
}

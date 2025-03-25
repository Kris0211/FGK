#include "../include/OrthogonalCamera.hpp"

OrthogonalCamera::OrthogonalCamera(unsigned int width, unsigned int height, 
	const rtx::Vector3& position, const rtx::Vector3& direction, 
	float orthoWidth, float orthoHeight) 
	: Camera(width, height, position, direction), orthogonalWidth(orthoWidth), orthogonalHeight(orthoHeight)
{
}

rtx::Ray OrthogonalCamera::GetRay(unsigned int x, unsigned int y)
{
	return rtx::Ray();
}

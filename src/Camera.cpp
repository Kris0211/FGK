#include "../include/Camera.hpp"

Camera::Camera(unsigned int width, unsigned int height, const rtx::Vector3& position, const rtx::Vector3& direction) 
	: width(width), height(height), position(position), direction(direction)
{
}

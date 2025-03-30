#include "../include/Buffer.hpp"

Buffer::Buffer(unsigned int width, unsigned int height) : width(width), height(height)
{
	colorBuffer.resize(width * height);
}

Buffer::~Buffer()
{
}

unsigned int Buffer::GetPixel(unsigned int x, unsigned int y) const
{
	return colorBuffer[x + width * y];
}

void Buffer::SetPixel(unsigned int x, unsigned int y, unsigned int color)
{
	colorBuffer[x + width * y] = color;
}

void Buffer::SetBufferColorFill(unsigned int color)
{
	for (int i = 0; i < width * height; ++i)
	{
		colorBuffer[i] = color;
	}
}

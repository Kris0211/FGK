#pragma once

#include <vector>

class Buffer
{
private:
	const unsigned int width;
	const unsigned int height;

	std::vector<unsigned int> colorBuffer;

public:
	Buffer(unsigned int width, unsigned int height);
	~Buffer();

	unsigned int GetWidth() const { return width; }
	unsigned int GetHeight() const { return height; }

	unsigned int GetPixel(unsigned int x, unsigned int y) const;
	void SetPixel(unsigned int x, unsigned int y, unsigned int color);

	const std::vector<unsigned int>& GetColorBuffer() { return colorBuffer; }

	void SetBufferColorFill(unsigned int color);

		
};


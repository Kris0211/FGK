#pragma once
#include <string>

class LightIntensity
{
public:
	float r, g, b;

	LightIntensity(const float R, const float G, const float B) : r(R), g(G), b(B) {}
	LightIntensity(const float R, const float G) : r(R), g(G), b(0) {}
	LightIntensity(const float R) : r(R), g(0), b(0) {}
	LightIntensity() : r(0), g(0), b(0) {}

	void operator()(const float R, const float G, const float B) { r = R; g = G; b = B; }
	void operator()(const float u) { r = u; g = u, b = u; }

	void Add(const float R, const float G, const float B);

	LightIntensity operator+(LightIntensity& li);
	LightIntensity operator-(LightIntensity& li);
	LightIntensity operator*(const float num);
	LightIntensity operator/(const float num);

	LightIntensity operator+=(LightIntensity& li);
	LightIntensity operator-=(LightIntensity& li);
	LightIntensity operator*=(const float num);
	LightIntensity operator/=(const float num);

	friend LightIntensity operator*(const float num, LightIntensity& li);
	friend LightIntensity operator*(LightIntensity& li, const float num);

	std::string ToString() const;
};

#include "../include/LightIntensity.hpp"

#include <sstream>

void LightIntensity::Add(const float R, const float G, const float B)
{
	r += R;
	g += G;
	b += B;
}

LightIntensity LightIntensity::operator+(LightIntensity& li)
{
	return { r + li.r, g + li.g, b + li.b };
}

LightIntensity LightIntensity::operator-(LightIntensity& li)
{
	return { r - li.r, g - li.g, b - li.b };
}

LightIntensity LightIntensity::operator*(const float num)
{
	return { r * num , g * num, b * num };
}

LightIntensity LightIntensity::operator/(const float num)
{
	return { r / num , g / num, b / num };
}

LightIntensity LightIntensity::operator+=(LightIntensity& li)
{
	r += li.r;
	g += li.g;
	b += li.b;

	return *this;
}

LightIntensity LightIntensity::operator-=(LightIntensity& li)
{
	r -= li.r;
	g -= li.g;
	b -= li.b;

	return *this;
}

LightIntensity LightIntensity::operator*=(const float num)
{
	r *= num;
	g *= num;
	b *= num;
	return *this;
}

LightIntensity LightIntensity::operator/=(const float num)
{
	r /= num;
	g /= num;
	b /= num;
	return *this;
}

LightIntensity operator*(const float num, LightIntensity& li)
{
	return LightIntensity(li.r * num, li.g * num, li.b * num);
}

LightIntensity operator*(LightIntensity& li, const float num)
{
	return LightIntensity(li.r * num, li.g * num, li.b * num);
}

std::string LightIntensity::ToString() const
{
	std::stringstream ss;
	ss << "Light intensity: r = " << this->r << ", g = " << this->g << ", b = " << this->b;
	return ss.str();
}

#pragma once
#include "../RasTerX/include/MathUtils.hpp"
#include "../RasTerX/include/Vector3.hpp"

struct Color
{
	unsigned char r, g, b, a;

	Color() :r(0), g(0), b(0), a(0xFF) {}
	Color(const int r, const int g, const int b, const int a = 255) :
		r(static_cast<unsigned char>(rtx::MathUtils::Clamp(r, 0, 255))),
		g(static_cast<unsigned char>(rtx::MathUtils::Clamp(g, 0, 255))),
		b(static_cast<unsigned char>(rtx::MathUtils::Clamp(b, 0, 255))),
		a(static_cast<unsigned char>(rtx::MathUtils::Clamp(a, 0, 255)))
	{
	}

	explicit Color(const float r, const float g, const float b, const float a = 1.0f) :
		r(static_cast<unsigned char>(rtx::MathUtils::Clamp(r, 0.0f, 1.0f) * 255)),
		g(static_cast<unsigned char>(rtx::MathUtils::Clamp(g, 0.0f, 1.0f) * 255)),
		b(static_cast<unsigned char>(rtx::MathUtils::Clamp(b, 0.0f, 1.0f) * 255)),
		a(static_cast<unsigned char>(rtx::MathUtils::Clamp(a, 0.0f, 1.0f) * 255))
	{
	}

	Color(unsigned int hex) :
		a((hex >> 24) & 0xFF),
		r((hex >> 16) & 0xFF),
		g((hex >> 8) & 0xFF),
		b(hex & 0xFF)
	{
	}

	Color(rtx::Vector3 v, const float a = 1.0f) :
		r(static_cast<unsigned char>(rtx::MathUtils::Clamp(v.x, 0.0f, 1.0f) * 255)),
		g(static_cast<unsigned char>(rtx::MathUtils::Clamp(v.y, 0.0f, 1.0f) * 255)),
		b(static_cast<unsigned char>(rtx::MathUtils::Clamp(v.z, 0.0f, 1.0f) * 255)),
		a(static_cast<unsigned char>(rtx::MathUtils::Clamp(a, 0.0f, 1.0f) * 255))
	{
	}

	unsigned int ToHex() const
	{
		return a << 24 | r << 16 | g << 8 | b;
	}

	rtx::Vector3 ToVector() const
	{
		return rtx::Vector3(
			static_cast<float>(r) / 255.0f,
			static_cast<float>(g) / 255.0f,
			static_cast<float>(b) / 255.0f
		);
	}
};

class Material
{
private:
	Color color;

public:
	Material();
	Material(Color color);
	~Material();

	Color GetColor() const;
	void SetColor(Color c);
};

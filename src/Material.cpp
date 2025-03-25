#include "../include/Material.hpp"

Material::Material()
{
	color = 0xFF000000;
}

Material::Material(unsigned int color) : color(color)
{
}

Material::~Material()
{
}

unsigned int Material::GetColor() const
{
	return color;
}

void Material::SetColor(unsigned int c)
{
	color = c;
}

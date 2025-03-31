#include "../include/Material.hpp"

Material::Material()
{
	color = Color();
}

Material::Material(Color color) : color(color)
{
}

Material::~Material()
{
}

Color Material::GetColor() const
{
	return color;
}

void Material::SetColor(Color c)
{
	color = c;
}

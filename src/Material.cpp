#include "../include/Material.hpp"

Material::Material()
{
	color = Color();
}

Material::Material(Color color) : color(color)
{
}

Material::Material(Color color, const float specular, const float specularCoeff, const float reflect)
{
}

Color Material::GetColor() const
{
	return this->color;
}

void Material::SetColor(Color c)
{
	color = c;
}

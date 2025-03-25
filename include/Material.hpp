#pragma once

class Material
{
private:
	unsigned int color;

public:
	Material();
	Material(unsigned int color);
	~Material();

	unsigned int GetColor() const;
	void SetColor(unsigned int c);
};

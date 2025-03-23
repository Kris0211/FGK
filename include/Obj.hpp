#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "../RasTerX/include/Triangle.hpp"

namespace RayTracer 
{

	class Obj 
	
	{
	public:
		Obj(const std::string& path);

		const std::vector<rtx::Triangle>& GetTriangles() const { return triangles; }

	private:
		std::vector<rtx::Triangle> triangles;

		void ParseObj(const std::string& path);
	};
}
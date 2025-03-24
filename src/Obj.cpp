#include "../include/Obj.hpp"

#include <cstdint>
#include <fstream>

//#define PRINT_DEBUG

namespace RayTracer 
{
	Obj::Obj(const std::string& path) 
	{
		ParseObj(path);
	}

	void Obj::ParseObj(const std::string& path) 
	{
        std::ifstream file(path);

		std::vector<rtx::Vector3> vertices;
		std::vector<unsigned int> vert_indices;

		std::vector<rtx::Vector3> normals;
		std::vector<unsigned int> norm_indices;

		std::string line;
		while (std::getline(file, line))
		{
			if (line[0] == '#') continue;

			char command[3];
			char parameters[30];

            sscanf_s(
                line.c_str(), "%s %[^\t\n]", 
                command, (unsigned)_countof(command), 
                parameters, (unsigned)_countof(parameters));

            if (strcmp(command, "v") == 0) {
                rtx::Vector3 vertex;
                sscanf_s(parameters, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
                vertices.push_back(vertex);
            }

            if (strcmp(command, "vn") == 0) {
                rtx::Vector3 normal;
                sscanf_s(parameters, "%f %f %f", &normal.x, &normal.y, &normal.z);
                normals.push_back(normal);
            }

            if (strcmp(command, "f") == 0) {
                unsigned int v1, v2, v3;
                unsigned int t1, t2, t3;
                unsigned int n1, n2, n3;

                sscanf_s(parameters,
                    "%i/%i/%i %i/%i/%i %i/%i/%i",
                    &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

                vert_indices.push_back(v1);
                vert_indices.push_back(v2);
                vert_indices.push_back(v3);

                norm_indices.push_back(n1);
                norm_indices.push_back(n2);
                norm_indices.push_back(n3);
            }
		}

#ifdef PRINT_DEBUG
        std::cout << vert_indices.size() << " " << norm_indices.size();
#endif

        for (int triangleID = 0; triangleID < std::trunc(vert_indices.size() / 3); ++triangleID) 
        {
            unsigned int indiceID = triangleID * 3;

            const unsigned int v1 = vert_indices[indiceID] - 1;
            const unsigned int v2 = vert_indices[indiceID + 1] - 1;
            const unsigned int v3 = vert_indices[indiceID + 2] - 1;

            const unsigned int n1 = norm_indices[indiceID] - 1;
            const unsigned int n2 = norm_indices[indiceID + 1] - 1;
            const unsigned int n3 = norm_indices[indiceID + 2] - 1;

            triangles.emplace_back(
                vertices[v1], vertices[v2], vertices[v3],
                normals[n1], normals[n2], normals[n3]
            );
        }
	}
}
#ifdef PRINT_DEBUG
    #undef PRINT_DEBUG
#endif

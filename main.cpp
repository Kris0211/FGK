#include <iostream>
#include <cmath>
#include <vector>

#include "RasTerX/include/Vector3.hpp"
#include "RasTerX/include/Ray.hpp"
#include "RasTerX/include/Sphere.hpp"
#include "RasTerX/include/Plane.hpp"
#include "RasTerX/include/Triangle.hpp"
#include "RasTerX/include/Matrix4.hpp"
#include "RasTerX/include/Vector4.hpp"
#include "RasTerX/include/Quaternion.hpp"

#include "include/Obj.hpp"
#include "include/Renderer.hpp"
#include "include/OrthographicCamera.hpp"
#include "include/PerspectiveCamera.hpp"
#include "include/PointLight.hpp"

constexpr unsigned int WIDTH = 512;
constexpr unsigned int HEIGHT = 512;

//#define PRINT_DEBUG

int main(int argc, char** argv)
{
	Renderer renderer{WIDTH, HEIGHT, 512, 16, 8};

	rtx::Sphere s1(rtx::Vector3(-0.5f, 0.f, 2.f), 0.33f);
	Material sm1(Color(0xFF0000FF), 0.8f, 5.f, 0.f);
	std::shared_ptr<SphereRenderable> sphere1 = std::make_shared<SphereRenderable>(sm1, s1);
	
	rtx::Sphere s2(rtx::Vector3(0.5f, 0.f, 2.f), 0.33f);
	Material sm2(Color(0xFFFF0000), 0.8f, 50.f, 0.f);
	std::shared_ptr<SphereRenderable> sphere2 = std::make_shared<SphereRenderable>(sm2, s2);
#if 0
	rtx::Sphere s3(rtx::Vector3(-0.5f, 0.5f, 2.f), 0.33f);
	Material sm3(Color(0xFF00FF00));
	std::shared_ptr<SphereRenderable> sphere3 = std::make_shared<SphereRenderable>(sm3, s3);

	rtx::Sphere s4(rtx::Vector3(0.5f, 0.5f, 2.f), 0.33f);
	Material sm4(Color(0xFFFFFF00));
	std::shared_ptr<SphereRenderable> sphere4 = std::make_shared<SphereRenderable>(sm4, s4);

	rtx::Sphere s5(rtx::Vector3(0.5f, -0.5f, 2.f), 0.33f);
	Material sm5(Color(0xFFFF00FF));
	std::shared_ptr<SphereRenderable> sphere5 = std::make_shared<SphereRenderable>(sm5, s5);
#endif

	renderer.AddRenderable(sphere1);
	renderer.AddRenderable(sphere2);
	//renderer.AddRenderable(sphere3);
	//renderer.AddRenderable(sphere4);
	//renderer.AddRenderable(sphere5);

	PointLight light1(rtx::Vector3(0.f, 0.f, 0.f), 
		LightIntensity(1.f, 1.f, 1.f), 1.f, 0.05f, 0.01f);
	std::shared_ptr<Light> pl1 = std::make_shared<PointLight>(light1);
	renderer.AddLight(pl1);

	std::shared_ptr<Camera> camera = std::make_shared<OrthographicCamera>(
		WIDTH, HEIGHT, rtx::Vector3(0, 0, -10.f), rtx::Vector3(0, 0, 1.f));

	std::shared_ptr<Camera> perspCamera = std::make_shared<PerspectiveCamera>(
		WIDTH, HEIGHT, 100.f, 90.f, rtx::Vector3(0, 0, -10.f), rtx::Vector3(0, 0, 1.f));

	std::cout << "Rendering images... Please wait.\n";

	renderer.Render(camera);
	renderer.Save("output1.tga");

	//renderer.Render(perspCamera);
	//renderer.Save("output2.tga");

	std::cout << "Complete!";

	return 0;
}

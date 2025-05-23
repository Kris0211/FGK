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
constexpr unsigned int SAMPLES_PER_PIXEL = 512;
constexpr unsigned int TILES_PER_ROW = 8;
constexpr unsigned int REFLECTION_LIMIT = 8;

//#define PRINT_DEBUG

int main(int argc, char** argv)
{
	Renderer renderer{WIDTH, HEIGHT, SAMPLES_PER_PIXEL, TILES_PER_ROW};
	
#pragma region SceneSetup
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(REFLECTION_LIMIT);

	// Spheres
	rtx::Sphere s1(rtx::Vector3(-0.8f, -2.f, 0.5f), 0.75f);
	Material sm1(Color(Color::GRAY), 0.5f, 5.f, 0.8f, 0.f);
	std::shared_ptr<SphereRenderable> sphere1 = std::make_shared<SphereRenderable>(sm1, s1);
	
	rtx::Sphere s2(rtx::Vector3(0.8f, -2.f, -0.5f), 0.75f);
	Material sm2(Color(Color::GRAY), 0.5f, 20.f, 0.f, 1.f);
	std::shared_ptr<SphereRenderable> sphere2 = std::make_shared<SphereRenderable>(sm2, s2);

	scene->AddRenderable(sphere1);
	scene->AddRenderable(sphere2);

	// Planes
	rtx::Plane p1(rtx::Vector3(4.f, 0.f, 0.f), rtx::Vector3(1.f, 0.f, 0.f));
	Material pm1(Color(Color::RED), 0.5f, 1.f, 0.f, 0.f);
	std::shared_ptr<PlaneRenderable> plane1 = std::make_shared<PlaneRenderable>(pm1, p1);
	
	rtx::Plane p2(rtx::Vector3(-4.f, 0.f, 0.f), rtx::Vector3(-1.f, 0.f, 0.f));
	Material pm2(Color(Color::GREEN), 0.5f, 1.f, 0.f, 0.f);
	std::shared_ptr<PlaneRenderable> plane2 = std::make_shared<PlaneRenderable>(pm2, p2);

	rtx::Plane p3(rtx::Vector3(0.f, 4.f, 0.f), rtx::Vector3(0.f, 1.f, 0.f));
	Material pm3(Color(Color::BLUE), 0.5f, 1.f, 0.f, 0.f);
	std::shared_ptr<PlaneRenderable> plane3 = std::make_shared<PlaneRenderable>(pm3, p3);

	rtx::Plane p4(rtx::Vector3(0.f, -4.f, 0.f), rtx::Vector3(0.f, -1.f, 0.f));
	Material pm4(Color(Color::CYAN), 0.5f, 1.f, 0.f, 0.f);
	std::shared_ptr<PlaneRenderable> plane4 = std::make_shared<PlaneRenderable>(pm4, p4);

	rtx::Plane p5(rtx::Vector3(0.f, 0.f, 4.f), rtx::Vector3(0.f, 0.f, 1.f));
	Material pm5(Color(Color::YELLOW), 0.5f, 1.f, 0.f, 0.f);
	std::shared_ptr<PlaneRenderable> plane5 = std::make_shared<PlaneRenderable>(pm5, p5);

	rtx::Plane p6(rtx::Vector3(0.f, 0.f, -8.f), rtx::Vector3(0.f, 0.f, -1.f));
	Material pm6(Color(Color::MAGENTA), 0.5f, 1.f, 0.f, 0.f);
	std::shared_ptr<PlaneRenderable> plane6 = std::make_shared<PlaneRenderable>(pm6, p6);
	
	scene->AddRenderable(plane1);
	scene->AddRenderable(plane2);
	scene->AddRenderable(plane3);
	scene->AddRenderable(plane4);
	scene->AddRenderable(plane5);
	//scene->AddRenderable(plane6);

	// Lights
	PointLight light1(rtx::Vector3(0.f, 1.f, -3.f), 
		LightIntensity(1.f, 1.f, 1.f), 1.f, 0.05f, 0.01f);
	std::shared_ptr<Light> pl1 = std::make_shared<PointLight>(light1);
	scene->AddLight(pl1);

#pragma endregion

	std::shared_ptr<Camera> camera = std::make_shared<OrthographicCamera>(
		WIDTH, HEIGHT, rtx::Vector3(0, 0, -10.f), rtx::Vector3(0, 0, 1.f));

	const float FOV = 90.f;
	std::shared_ptr<Camera> perspCamera = std::make_shared<PerspectiveCamera>(
		WIDTH, HEIGHT, 10.f, FOV, rtx::Vector3(0, 0, -4.0f), rtx::Vector3::Zero());

	std::cout << "Rendering images... Please wait.\n";

	//renderer.Render(camera, scene);
	//renderer.Save("o_orho.tga");

	renderer.Render(perspCamera, scene);
	renderer.Save("o_persp.tga");

	std::cout << "Complete!";

	return 0;
}

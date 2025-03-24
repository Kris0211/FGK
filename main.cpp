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

//#define PRINT_DEBUG

int main(int argc, char** argv)
{
	// VECTORS
	std::cout << "===VECTORS==\n";
	rtx::Vector3 vectorA = rtx::Vector3(1, 2, 3);
	rtx::Vector3 vectorB = rtx::Vector3(3, 4, 5);

	rtx::Vector3 sumAB = vectorA + vectorB;
	rtx::Vector3 sumBA = vectorB + vectorA;

	std::cout << "Sum A+B: " << sumAB.ToString() << "\nSum B+A: " << sumBA.ToString() << std::endl;

	rtx::Vector3 vectorC = rtx::Vector3(0, 3, 0);
	rtx::Vector3 vectorD = rtx::Vector3(5, 5, 0);

	std::cout << "Angle between C and D: " << rtx::Vector3::AngleBetween(vectorC, vectorD) << std::endl;

	rtx::Vector3 vectorE = rtx::Vector3(4, 5, 1);
	rtx::Vector3 vectorF = rtx::Vector3(4, 1, 3);

	rtx::Vector3 perpendicular = rtx::Vector3::CrossProduct(vectorE, vectorF);

	std::cout << "Vector perpendicular to E and F: " << perpendicular.ToString() << std::endl;

	rtx::Vector3 normalized = perpendicular.Normal();
	std::cout << "Normalized vector: " << normalized.ToString() << std::endl;


	// SPHERE
	std::cout << "\n\n===SPHERE INTERSECTIONS==\n";

	rtx::Sphere s = rtx::Sphere(rtx::Vector3::Zero(), 10.f);
	rtx::Ray r1 = rtx::Ray(rtx::Vector3(0, 0, -20), s.center);
	rtx::Ray r2 = rtx::Ray(rtx::Vector3(0, 0, -20), rtx::Vector3::Up(), FLT_MAX);
	rtx::Vector3 ip1 = rtx::Vector3();
	rtx::Vector3 ip2 = rtx::Vector3();

	bool intersects1 = s.Intersects(r1, ip1);
	bool intersects2 = s.Intersects(r2, ip2);

	std::cout << "Ray 1 spehere intersection: " << (intersects1 ? "true" : "false") 
		<< "\nIntersection point: " << (intersects1 ? ip1.ToString() : "N/A") << std::endl;
	std::cout << "Ray 2 spehere intersection: " << (intersects2 ? "true" : "false")
		<< "\nIntersection point: " << (intersects2 ? ip2.ToString() : "N/A") << std::endl;
	
	rtx::Ray r3 = rtx::Ray(rtx::Vector3(10, -10, 0), rtx::Vector3::Up(), FLT_MAX);
	rtx::Vector3 ip3 = rtx::Vector3();
	bool intersects3 = s.Intersects(r3, ip3);
	std::cout << "Ray 3 spehere intersection: " << (intersects3 ? "true" : "false")
		<< "\nIntersection point: " << (intersects3 ? ip3.ToString() : "N/A") << std::endl;


	// PLANE
	std::cout << "\n\n===PLANE INTERSECTIONS==\n";

	rtx::Vector3 normal = rtx::Vector3(1.f, std::sqrtf(2.f), std::sqrtf(2.f)).Normal();
	rtx::Plane p = rtx::Plane(normal, rtx::Vector3::Zero());

	rtx::Vector3 ip_p2;

	bool intersects_p2 = p.Intersects(r2, ip_p2);
	std::cout << "Ray 2 plane intersection: " << (intersects_p2 ? "true" : "false")
		<< "\nIntersection point: " << (intersects_p2 ? ip_p2.ToString() : "N/A") << std::endl;


	// TRINGLE
	std::cout << "\n\n===TRIANGLE INTERSECTIONS==\n";
	rtx::Vector3 a = rtx::Vector3::Zero();
	rtx::Vector3 b = rtx::Vector3(1.f, 0.f, 0.f);
	rtx::Vector3 c = rtx::Vector3(0.f, 1.f, 0.f);

	rtx::Triangle t = rtx::Triangle(a, b, c);

	// Przypadek 1: Linia przechodz¹ca przez trójk¹t
	rtx::Vector3 p1 = rtx::Vector3(-1.f, 0.5f, 0.f);
	rtx::Vector3 p2 = rtx::Vector3(1.f, 0.5f, 0.f);
	
	rtx::Ray tr1 = rtx::Ray(p1, p2);
	rtx::Vector3 ip_t;

	bool intersetcs_t1 = t.Intersects(tr1, ip_t);
	std::cout << "Case 1 ray triangle intersection: " << (intersetcs_t1 ? "true" : "false")
		<< "\nIntersection point: " << (intersetcs_t1 ? ip_t.ToString() : "N/A") << std::endl;

	// Przypadek 2: Linia le¿¹ca na p³aszczyŸnie trójk¹ta, ale poza nim
	p1 = rtx::Vector3(2.f, -1.f, 0.f);
	p2 = rtx::Vector3(2.f, 2.f, 0.f);

	rtx::Ray tr2 = rtx::Ray(p1, p2);

	bool intersetcs_t2 = t.Intersects(tr2, ip_t);
	std::cout << "Case 2 ray triangle intersection: " << (intersetcs_t2 ? "true" : "false")
		<< "\nIntersection point: " << (intersetcs_t2 ? ip_t.ToString() : "N/A") << std::endl;

	// Przypadek 3: Linia nieprzecinaj¹ca trójk¹ta
	p1 = rtx::Vector3(0.f, 0.f, -1.f);
	p2 = rtx::Vector3(0.f, 0.f, 1.f);

	rtx::Ray tr3 = rtx::Ray(p1, p2);

	bool intersetcs_t3 = t.Intersects(tr3, ip_t);
	std::cout << "Case 3 ray triangle intersection: " << (intersetcs_t3 ? "true" : "false")
		<< "\nIntersection point: " << (intersetcs_t3 ? ip_t.ToString() : "N/A") << std::endl;


	// MATRICES
	std::cout << "\n\n===MATRICES===\n";

	float val1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	float val2[16] = { 1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6, 4, 5, 6, 7 };
	float val3[16] = { 2, 3, 4, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, 1 };
	rtx::Matrix4 mat1 = rtx::Matrix4(val1);
	std::cout << "Matrix 1:\n";
	mat1.PrintMatrix();
	rtx::Matrix4 mat2 = rtx::Matrix4(val2);
	std::cout << "Matrix 2:\n";
	mat2.PrintMatrix();
	rtx::Matrix4 mat3 = rtx::Matrix4(val3);
	std::cout << "Matrix 3:\n";
	mat2.PrintMatrix();

	{
		mat1.Add(mat2);
		std::cout << "\nSum:\n";
		mat1.PrintMatrix();

		mat1 = rtx::Matrix4(val1);
		mat1.Sub(mat2);
		std::cout << "\nDifference:\n";
		mat1.PrintMatrix();

		mat1 = rtx::Matrix4(val1);
		mat1.Mul(5);
		std::cout << "\nMultiplied by 5:\n";
		mat1.PrintMatrix();

		mat1 = rtx::Matrix4(val1);
		mat1.Transpose();
		std::cout << "\nTransposed:\n";
		mat1.PrintMatrix();

		// https://www.wolframalpha.com/input?key=&i2d=true&i=%7B%7B2%2C3%2C4%2C-1%7D%2C%7B1%2C1%2C-1%2C1%7D%2C%7B1%2C-1%2C1%2C1%7D%2C%7B-1%2C1%2C1%2C1%7D%7D
		mat1 = rtx::Matrix4(val3);
		mat1.Invert();
		std::cout << "\nInverse:\n";
		mat1.PrintMatrix();

		mat1.LoadIdentity();
		std::cout << "\nIdentity:\n";
		mat1.PrintMatrix();

		rtx::Vector3 vect = rtx::Vector3(5, 10, 15);

		mat1.SetTranslation(vect);
		std::cout << "\nTranslation by [5, 10, 15]:\n";
		mat1.PrintMatrix();

		mat1.LoadIdentity();
		mat1.SetScale(vect);
		std::cout << "\nScale by [5, 10, 15]:\n";
		mat1.PrintMatrix();

		mat1.LoadIdentity();
		mat1.SetScale(3);
		std::cout << "\nUniform scale by 3:\n";
		mat1.PrintMatrix();

		mat1.LoadIdentity();
		mat1.SetRotationX(PI / 6);
		std::cout << "\nX rotation, 30 degrees:\n";
		mat1.PrintMatrix();

		mat1.LoadIdentity();
		mat1.SetRotationY(PI / 4);
		std::cout << "\nY rotation, 45 degrees:\n";
		mat1.PrintMatrix();

		mat1.LoadIdentity();
		mat1.SetRotationZ(PI / 3);
		std::cout << "\nZ rotation, 60 degrees:\n";
		mat1.PrintMatrix();

		mat1.LoadIdentity();
		mat1.SetRotationAxis(PI / 2, vect);
		std::cout << "\nRotation matrix:\n";
		mat1.PrintMatrix();
	}

	//Test obrotu wektora
	{
		std::cout << "\n--ROTATION--";
		mat1.SetRotationY(PI * 0.5);
		rtx::Vector4 vec = rtx::Vector4(1, 0, 0, 1);
		rtx::Vector4 result = mat1 * vec;
		std::cout << "\nVector [1, 0, 0, 1] after rottion:\n" << result.ToString();
	}

	//Test (braku) przemiennosci mnozenia macierzy
	{
		mat1 = rtx::Matrix4(val1);
		mat2 = rtx::Matrix4(val2);
		rtx::Matrix4 mat3 = mat1 * mat2;
		std::cout << "\nMatrix1 x Matrix2:\n";
		mat3.PrintMatrix();
		rtx::Matrix4 mat4 = mat2 * mat1;
		std::cout << "\nMatrix2 x Matrix1:\n";
		mat4.PrintMatrix();
	}


	// QUATERNIONS
	std::cout << "\n\n===QUATERNIONS===\n";
	
	rtx::Vector3 vect1 = rtx::Vector3(3.f, 1.f, 3.f);
	rtx::Quaternion quat1 = rtx::Quaternion(PI / 2, rtx::Vector3(1.f, 0.f, 1.f).Normal());
	rtx::Vector3 result = quat1.RotateVectorByQuaternion(vect1);
	std::cout << "Vector: " << vect1.ToString() << " rotated by Quaternion: " << quat1.ToString() << " \n= " << result.ToString() << std::endl;

	rtx::Quaternion quat2 = rtx::Quaternion::RotationQuaternion(PI / 6, rtx::Vector3(1.f, 0.f, 0.f));

	float quat2_mag = quat2.Magnitude();
	std::cout << "Magnitude: " << quat2_mag << std::endl;

	rtx::Quaternion quat2_inv = rtx::Quaternion::InvertQuaternion(quat2);
	std::cout << "Inverted: " << quat2_inv.ToString() << std::endl;

	rtx::EulerAngles eulers = rtx::Quaternion::QuaternionToEuler(quat2);
	std::cout << "Euler angles:"
		<< "\nPitch: " << rtx::MathUtils::RadToDeg(eulers.pitch)
		<< "\nYaw:" << rtx::MathUtils::RadToDeg(eulers.yaw)
		<< "\nRoll:" << rtx::MathUtils::RadToDeg(eulers.roll)
		<< "\n\n";

	rtx::Quaternion quatA = rtx::Quaternion(0.233f, 0.06f, -0.257f, -0.935f);
	rtx::Quaternion quatB = rtx::Quaternion(-0.752f, 0.286f, 0.374f, 0.459f);
	
	std::cout << "Dot product of quatA and quatB: " << quatA.Dot(quatB) << std::endl;
	std::cout << "Quat product of quatA and quatB: " << (quatA * quatB).ToString() << std::endl;
	std::cout << "Difference: " << (quatA - quatB).ToString() << std::endl;


	// OBJ
	RayTracer::Obj monkey = RayTracer::Obj("res/monkey.obj");

#ifdef PRINT_DEBUG
	std::cout << "\n\n";
	for (const rtx::Triangle& t : monkey.GetTriangles())
	{
		std::cout << "\nA: " << t.GetVertA().ToString() << " | B: " << t.GetVertB().ToString() << " | C: " << t.GetVertC().ToString();
	}
#endif

	return 0;
}
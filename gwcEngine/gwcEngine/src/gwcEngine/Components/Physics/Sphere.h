#pragma once
#include"glm/glm.hpp"
#include "Ray.h"
namespace gwcEngine
{
	class Sphere
	{
	public:
		Sphere();
		Sphere(glm::vec3 origin, float radius);

		bool Intersect(const Ray& ray);
		bool Intersect(const Sphere& other);
	protected:
		glm::vec3 m_Origin = glm::vec3(0);
		float m_Radius = 1.0f;
	};
}
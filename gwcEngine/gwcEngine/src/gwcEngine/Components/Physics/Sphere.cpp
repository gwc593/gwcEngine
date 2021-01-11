#include "gepch.h"
#include "Sphere.h"
#include "glm/gtx/norm.hpp"
namespace gwcEngine
{
	Sphere::Sphere()
	{
		
	}

	Sphere::Sphere(glm::vec3 origin, float radius):m_Origin(origin), m_Radius(radius) {};

	bool Sphere::Intersect(const Ray& ray)
	{
		return (glm::dot(ray.GetDirection(), (ray.GetOrigin() - m_Origin)) * glm::dot(ray.GetDirection(), (ray.GetOrigin() - m_Origin))) - (glm::length2(ray.GetOrigin() - m_Origin) - (m_Radius * m_Radius)) >= 0;
	}

	bool Sphere::Intersect(const Sphere& other)
	{
		return glm::length(other.m_Origin - m_Origin) <= (other.m_Radius + m_Radius);
	}
}
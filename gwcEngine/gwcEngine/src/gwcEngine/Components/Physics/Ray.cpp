#include "gepch.h"
#include "Ray.h"

namespace gwcEngine
{
	Ray::Ray(const Ref<Camera>& camera, float clipX, float clipY)
	{
		Ref<Transform> transform = (*camera)->GetTransform();

		//Get origin
		m_Origin = transform->GetPosition();

		//Get Direction
		glm::vec3 world = (*camera)->ClipToWorld(clipX, clipY);

		GE_CORE_ASSERT(false, "need to impliment Ray system, probably a line renderer so i can see what the hell im making too!");
		m_Direction = { 0,0,0 };
	}
}
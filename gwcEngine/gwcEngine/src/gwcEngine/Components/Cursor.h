#pragma once
#include "gwcEngine/ECS/Entity.h"
#include <glm/glm.hpp>

namespace gwcEngine 
{

	class Cursor
	{
	public:
		static Cursor* GetInstance();
		static GameObject GetHeldObject() { return GetInstance()->m_HeldObject; }
		static const glm::vec3 GetRay();
		

	private:
		Cursor() = default;

		void Init();

		static Cursor* s_Instance;
		GameObject m_HeldObject;
		
		Ref<EventCallback<float, float>> m_MouseMovedCB;
		
		std::tuple<int32_t, int32_t> m_Position;
	};
}
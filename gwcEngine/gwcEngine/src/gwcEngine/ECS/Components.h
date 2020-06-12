#pragma once
#include"ECS.h"
#include"gwcEngine/Components/Mesh.h"

//todo class for each component

namespace gwcEngine
{
	class Position2D : public Component
	{
	public:

		float GetX() { return m_posX; }
		float GetY() { return m_posY; }

		void SetX(float in) { m_posX = in; }
		void SetY(float in) { m_posY = in; }

		void Init() override
		{
			GE_CORE_TRACE("position 2d component initialised...");
		}

	private:

		float m_posX = 0.0f;
		float m_posY = 0.0f;
	};
}
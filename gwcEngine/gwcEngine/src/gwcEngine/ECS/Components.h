#pragma once
#include"ECS.h"
#include"gwcEngine/Components/Mesh.h"

//todo class for each component

namespace gwcEngine
{
	class PositionComponent : public Component
	{
	public:
		int GetPosX() { return xpos; }
		int GetPosY() { return ypos; }
		int GetPosZ() { return zpos; }

		void SetPosX(int in) { xpos = in; }
		void SetPosY(int in) { ypos = in; }
		void SetPosZ(int in) { zpos = in; }

		void OnUpdate() override
		{
			GE_CORE_TRACE("component is working....");
		}

	private:
		int xpos=0, ypos=0, zpos=0;
	};
}
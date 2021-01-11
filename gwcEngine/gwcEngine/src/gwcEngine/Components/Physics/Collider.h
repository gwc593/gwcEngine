#pragma once

namespace gwcEngine 
{
	class Collider
	{
	public:
		Collider() = default;
		~Collider() = default;

		
	protected:
		void SetOwner(GameObject owner) { m_Owner = owner; }
		std::vector<GameObject> m_Collisions;
		GameObject m_Owner;
	};
}
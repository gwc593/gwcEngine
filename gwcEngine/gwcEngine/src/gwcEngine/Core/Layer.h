#pragma once
#include"core.h"
#include"gwcEngine/Events/Event.h"
#include "gwcEngine/ECS/ECS.h"



namespace gwcEngine {
	class GE_API Layer
	{
	public:
		Layer(const std::string& name = "unNamedLayer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		void OnUpdateBase();
		virtual void OnEvent(Event& e) {}

		inline const ECSManager& GetManager() const { return m_LayerManager; }


		//todo gwc - do not allow this in dist builds
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;

		ECSManager m_LayerManager;
		
	};
}



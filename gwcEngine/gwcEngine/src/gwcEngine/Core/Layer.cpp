#include "gepch.h"
#include "Layer.h"

namespace gwcEngine 
{
	Layer::Layer(const std::string& name)
	{
		m_DebugName = name;
		m_LayerManager = new ECSManager;
	}

	Layer::~Layer()
	{
		delete m_LayerManager;
	}

	void Layer::OnUpdateBase()
	{
		//Base behaviour
		m_LayerManager->OnUpdate();
		OnUpdate();

	}

	bool Layer::OnEventBase( Event& e)
	{
		bool state = false;
		state = state |m_LayerManager->OnEvent(e);
		return state |OnEvent(e);
	}

	bool Layer::OnEvent(Event& e)
	{
		return false;
	}

}

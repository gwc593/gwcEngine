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

		OnUpdate();

	}
}

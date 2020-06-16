#include "gepch.h"
#include "Layer.h"

namespace gwcEngine 
{
	Layer::Layer(const std::string& name)
	{
		m_DebugName = name;

	}

	Layer::~Layer()
	{

	}

	void Layer::OnUpdateBase()
	{
		//Base behaviour

		OnUpdate();

	}

	bool Layer::OnEventBase( Event& e)
	{
		return e.Handled || OnEvent(e);
	}

	bool Layer::OnEvent(Event& e)
	{
		return e.Handled;
	}

}

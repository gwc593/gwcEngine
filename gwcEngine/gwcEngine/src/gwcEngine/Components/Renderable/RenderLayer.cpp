#include"gepch.h"
#include"RenderLayer.h"

namespace gwcEngine
{
	std::bitset<MAX_RENDER_LAYERS> RenderLayer::s_Layers;
	std::unordered_map<std::string, uint16_t> RenderLayer::s_NameMap;

	uint16_t RenderLayer::s_NextID = 0;

	int16_t RenderLayer::GetLayerID(const std::string& name)
	{
		auto temp = s_NameMap.find(name);
		if (temp != s_NameMap.end())
			return temp->second;

		GE_CORE_WARN("{0} is not a valid render Layer", name);
		return -1;
	}


	int16_t RenderLayer::RegisterLayer(const std::string& name)
	{
		auto temp = s_NameMap.find(name);
		if (temp != s_NameMap.end())
			return temp->second;

		if (s_NextID == MAX_RENDER_LAYERS) {
			GE_CORE_WARN("Maximum render layers reached: {0} has not been added to render layer stack", name);
			return -1;
		}

		s_NameMap[name] = s_NextID++;

		return s_NextID - 1;
	}


	std::vector<std::string> RenderLayer::GetLayers()
	{
		std::vector<std::string> ret;

		for (auto element : s_NameMap) {
			ret.push_back(element.first);
		}

		return ret;
	}

	void RenderLayer::ActivateLayer(const std::string& name)
	{
		auto id = GetLayerID(name);

		if (id != -1) {
			m_ActiveLayers[id] = true;
		}
	}

	void RenderLayer::DeactivateLayer(const std::string& name)
	{
		auto id = GetLayerID(name);

		if (id != -1) {
			m_ActiveLayers[id] = false;
		}
	}

	void RenderLayer::DeactivateAll()
	{
		m_ActiveLayers.reset();
	}

	void RenderLayer::ActivateAll()
	{
		m_ActiveLayers.set();
	}
}
#pragma once

namespace gwcEngine 
{
#define MAX_RENDER_LAYERS 32
	class RenderLayer
	{
	public:
	
		RenderLayer() = default;
		~RenderLayer() = default;

		//find a layer ID
		static int16_t GetLayerID(const std::string& name);

		//register Layer
		static int16_t RegisterLayer(const std::string& name);

		//get valid layer names
		static std::vector<std::string> GetLayers();

		//activate a layer
		void ActivateLayer(const std::string& name);

		//deactivate a layer
		void DeactivateLayer(const std::string& name);

		//deactivate all layers
		void DeactivateAll();

		//activate all layers
		void ActivateAll();

		const std::bitset<MAX_RENDER_LAYERS>& GetActiveLayers() const { return m_ActiveLayers; }



	protected:
		static std::bitset<MAX_RENDER_LAYERS> s_Layers;
		static std::unordered_map<std::string, uint16_t> s_NameMap;
		static uint16_t s_NextID;

		std::bitset<MAX_RENDER_LAYERS> m_ActiveLayers;
	};
}
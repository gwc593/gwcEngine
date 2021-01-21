#pragma once
#include"glm/glm.hpp"
namespace gwcEngine
{
	enum class LightType
	{
		Point = 0,
		Directional,
		Spot
	};

	struct LightProps  //shader compliant light data structure.
	{
		bool isEnabled = false;
		bool isLocal = false; //true for point and spot
		bool isSpot = false;
		glm::vec3 ambient = { 0,0,0 };
		glm::vec3 colour = { 0,0,0 };
		glm::vec3 position = { 0,0,0 };
		glm::vec3 halfVector = { 0,0,0 }; //h := ( v + l ) / || v + l || ;   viewer, light have been normalised
		glm::vec3 coneDirection = { 0,0,0 };
		float spotCutoff = 0;
		float spotExponent = 0;
		float constantAttenuation = 0;
		float linearAttenuation = 0;
		float quadraticAttenuation = 0;
	}; 


	class Light
	{
	public:
		Light()
		{
			SetType(LightType::Directional);
			SetColour({ 0.3,0.3,0.3 });
			SetScatterAmount(0.f);
		}

		Light(const LightType& type)
		{
			SetType(type);
			SetColour({ 0.3,0.3,0.3 });
			SetScatterAmount(0.f);
		}


		~Light();

		const LightProps& GetProperties()const { return m_LightProps; }

		void SetType(const LightType& type) 
		{
			m_Type = type;

			switch (type) {
			case LightType::Point: {
				assert(false);
				m_LightProps.isLocal = true;
				m_LightProps.isSpot = false;
			}
			case LightType::Spot: {
				assert(false);
				m_LightProps.isLocal = true;
				m_LightProps.isSpot = true;
			}
			case LightType::Directional: {
				
				m_LightProps.isLocal = false;
				m_LightProps.isSpot = false;
			}

			default:
				break;
			}
		}

		void SetColour(const glm::vec3& colour) { m_LightProps.colour = colour; m_LightProps.ambient = colour * m_AmbientContribution; }
		void SetScatterAmount(const float& amount) { m_AmbientContribution = amount; m_LightProps.ambient = m_LightProps.colour * m_AmbientContribution;}

	protected:
		//Light Source Type
		LightType m_Type;
		
		//Ambient Properties
		float m_AmbientContribution;

		LightProps m_LightProps;
	};
}

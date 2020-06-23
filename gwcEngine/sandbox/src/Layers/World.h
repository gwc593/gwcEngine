#pragma once
#include <gwcEngine.h>



class CustomEvent : public gwcEngine::Event
{
public:
	CustomEvent()
	{

	}
	EVENT_CLASS_CATEGORY(gwcEngine::None)

		std::string ToString() const override
	{
		std::stringstream ss;
		ss << "Custom Event Raised ";
		return ss.str();
	}

	//EVENT_CLASS_TYPE(None)
	//TODO gwc: Get the above macro working for custom events.
	static gwcEngine::EventType GetStaticType() { return gwcEngine::EventType::None; }
	virtual gwcEngine::EventType GetEventType() const override { return GetStaticType(); }
	virtual const char* GetName() const override { return "None"; }


private:

};

class World : public gwcEngine::Layer
{
public:
	World();

	void CameraController();

	void OnUpdate() override;

	bool onClicked(const gwcEngine::MouseButtonPressedEvent& e);

	bool onSpaceBar(const gwcEngine::KeyPressedEvent& e);

	bool OnEvent(gwcEngine::Event& event) override;

private:
	gwcEngine::PerspectiveCamera m_Camera;

	std::shared_ptr<gwcEngine::Shader> m_UnlitColourShader;
	gwcEngine::Material m_UnlitColour;

	float m_squareRotation = 0.0f;
	float m_camerRot = 0.0f;

	gwcEngine::Mesh tri;
	gwcEngine::Ref<gwcEngine::Entity> triangleEntity;

	gwcEngine::ECSLayerManager m_ECS_Manager;
};


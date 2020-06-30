#pragma once
#include <gwcEngine.h>



class World : public gwcEngine::Layer
{
public:
	World();

	void CameraController();

	void OnUpdate() override;

	//test callbacks
	bool onPPressed(int key);
	bool onPPressedUI(int key);

private:
	gwcEngine::PerspectiveCamera m_Camera;

	std::shared_ptr<gwcEngine::Shader> m_UnlitColourShader;

	float m_squareRotation = 0.0f;
	float m_camerRotY = 0.0f;
	float m_camerRotX = 0.0f;

	gwcEngine::Ref<gwcEngine::Entity> CubeEntity;

	gwcEngine::ECSLayerManager m_ECS_Manager;
	std::pair<float, float> mouse;
};


#pragma once
#include <gwcEngine.h>



class Env3D : public gwcEngine::Layer
{
public:
	Env3D();

	void CameraController();

	void OnUpdate() override;
	void OnAttach() override;

	//test callbacks
	bool onPPressed(int key);
	bool onPPressedUI(int key);

	gwcEngine::Ref<gwcEngine::FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }

private:
	gwcEngine::PerspectiveCamera m_Camera;

	std::shared_ptr<gwcEngine::Shader> m_UnlitColourShader;

	float m_squareRotation = 0.0f;
	float m_camerRotY = 0.0f;
	float m_camerRotX = 0.0f;
	
	gwcEngine::Ref<gwcEngine::Entity> CubeEntity;

	gwcEngine::ECSLayerManager m_ECS_Manager;
	std::pair<float, float> mouse;

	gwcEngine::Ref<gwcEngine::FrameBuffer> m_FrameBuffer;
};


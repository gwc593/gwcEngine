#pragma once
#include <gwcEngine.h>

class Env3D : public gwcEngine::Layer
{
public:
	Env3D();

	void CameraController(gwcEngine::Ref<gwcEngine::Camera> camera);

	void OnUpdate() override;
	void OnAttach() override;

	//test callbacks
	bool onPPressed(int key);
	bool onPPressedUI(int key);

	gwcEngine::Ref<gwcEngine::FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }

private:
	gwcEngine::Ref<gwcEngine::PerspectiveCamera> m_PCamera;
	gwcEngine::Ref<gwcEngine::OrthographicCamera> m_UICamera;

	gwcEngine::Ref<gwcEngine::Shader> m_UnlitColourShader;
	std::shared_ptr<gwcEngine::Shader> m_UnlitTexturedShader;

	float m_squareRotation = 0.0f;
	float m_camerRotY = 0.0f;
	float m_camerRotX = 0.0f;
	
	gwcEngine::Ref<gwcEngine::Entity> m_CubeEntity;

	gwcEngine::ECSLayerManager m_ECS_Manager;
	std::pair<float, float> mouse;

	gwcEngine::Ref<gwcEngine::FrameBuffer> m_FrameBuffer;

private: //temp
	gwcEngine::Mesh FullScreenQuad;
};


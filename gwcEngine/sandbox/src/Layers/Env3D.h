#pragma once
#include <gwcEngine.h>

class Env3D : public gwcEngine::Layer
{
public:
	Env3D();

	void CameraController(gwcEngine::Ref<gwcEngine::Camera> camera);

	void OnUpdate() override;
	void OnAttach() override;
		
	void AnimateCube();

	gwcEngine::Ref<gwcEngine::OrthographicCamera> m_WindowCamera;
private:
	gwcEngine::Ref<gwcEngine::PerspectiveCamera> m_PCamera;

	gwcEngine::Ref<gwcEngine::Shader> m_UnlitColourShader;
	std::shared_ptr<gwcEngine::Shader> m_UnlitTexturedShader;

	float m_squareRotation = 0.0f;
	float m_camerRotY = 0.0f;
	float m_camerRotX = 0.0f;
	
	gwcEngine::Ref<gwcEngine::Entity> m_CubeEntity;

	gwcEngine::ECSLayerManager m_ECS_Manager;

private: //temp
	gwcEngine::Panel m_ViewPortPanel;

};


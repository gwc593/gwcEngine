#pragma once
#include <gwcEngine.h>

class Env3D : public gwcEngine::Layer
{
public:
	Env3D();

	void CameraController(gwcEngine::Ref<gwcEngine::Camera> camera);

	void OnUpdate() override;
	void OnAttach() override;
		
	void AnimateCube(gwcEngine::Ref<gwcEngine::Entity> gameObject, float offset = 0.0f);

	//todo NEXT make singleton
	gwcEngine::Ref<gwcEngine::OrthographicCamera> m_WindowCamera;
private:
	gwcEngine::Ref<gwcEngine::PerspectiveCamera> m_PCamera;
	
	gwcEngine::Ref<gwcEngine::Entity> m_CubeEntity;
	gwcEngine::Ref<gwcEngine::Entity> m_quad;

	gwcEngine::ECSLayerManager m_ECS_Manager;

private: //temp
	gwcEngine::Panel m_ViewPortPanel;

};


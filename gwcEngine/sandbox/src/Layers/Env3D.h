#pragma once
#include <gwcEngine.h>

class Env3D : public gwcEngine::Layer
{
public:
	Env3D();

	void OnUpdate() override;
	void OnAttach() override;
		
	void AnimateEntity(gwcEngine::GameObject gameObject, float offset = 0.0f);

private:
	
	gwcEngine::ECSManager* m_ECS_Manager;

};


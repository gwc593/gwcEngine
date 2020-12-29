#pragma once
#include <gwcEngine.h>

class DebugCam : public gwcEngine::Layer
{
public:
	DebugCam() = default;

	void OnAttach() override;
};
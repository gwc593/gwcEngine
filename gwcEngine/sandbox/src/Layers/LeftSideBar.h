#pragma once
#include<gwcEngine.h>

class LeftSideBar : public gwcEngine::Layer
{
public:
	LeftSideBar();
	~LeftSideBar() = default;

	void OnAttach() override;
};
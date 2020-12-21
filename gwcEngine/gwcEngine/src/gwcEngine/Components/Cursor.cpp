#include"gepch.h"
#include "Cursor.h"
#include "gwcEngine/Core/Input.h"
#include "gwcEngine/Core/application.h"
#include "gwcEngine/Renderer/Cameras/OrthographicCamera.h"
namespace gwcEngine 
{

	Cursor* Cursor::s_Instance = nullptr;

	void Cursor::Init()
	{
		m_HeldObject = nullptr;

		m_MouseMovedCB.reset(new EventCallback<float, float>(
			[this](float x, float y)
			{
				std::get<0>(m_Position) = (int32_t)x; 
				std::get<1>(m_Position) = (int32_t)y;  
				GetRay();
				return PROPAGATE_EVENT; 
			}
			)
		);

		Input::GetMouseMovedEvent().subscribe(m_MouseMovedCB);
	}

	Cursor* Cursor::GetInstance()
	{
		if (s_Instance != nullptr)
			return s_Instance;

		s_Instance = new Cursor;
		//init held object
		s_Instance->Init();

		return s_Instance;
	}

	const glm::vec3 Cursor::GetRay()
	{
		Ref<OrthographicCamera> camera = Application::Get()->GetWindow().GetCamera();
		
		//generate clip space position
		auto& window = Application::Get()->GetWindow();
		float mX, mY, cx, cy, clipX, clipY;

		mX = (2.0f) / (float(window.GetWidth()));
		mY = (-2.0f) / (float(window.GetHeight()));

		cx = 1.0f - (mX * float(window.GetWidth()));
		cy = 1.0f + (mY * float(window.GetHeight()));


		clipX = (mX * (float)(std::get<0>(s_Instance->m_Position))) + cx;
		clipY = (mY * (float)(std::get<1>(s_Instance->m_Position))) - cy;

		auto ray = camera->ClipToWorld(clipX, clipY);
		ray.z = -1.0;
		GE_CORE_TRACE("Top Level Ray = ({0},{1},{2})", ray.x,ray.y,ray.z);
		return ray;
	}

}
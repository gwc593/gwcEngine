#pragma once

#include"gepch.h"
//For use in gwcEngine applications
#include"gwcEngine/Core/application.h"
#include "gwcEngine/Core/Layer.h"
#include "gwcEngine/Core/Log.h"

//Entity component System
//temp


#include "gwcEngine/Core/Time.h"

#include "gwcEngine/Core/KeyCodes.h"
#include "gwcEngine/Core/MouseButtonCodes.h"
#include "gwcEngine/Core/Input.h"

#include "gwcEngine/Renderer/Renderer.h"
#include "gwcEngine/Renderer/RenderCommand.h"
#include "gwcEngine/Renderer/Material.h"

#include "gwcEngine/Renderer/Shader/Buffer.h"
#include "gwcEngine/Renderer/Shader/Shader.h"
#include "gwcEngine/Renderer/Shader/VertexArray.h"

#include "gwcEngine/Renderer/Cameras/OrthographicCamera.h"
#include "gwcEngine/Renderer/Cameras/PerspectiveCamera.h"

////events///
#include "gwcEngine/Events/ApplicationEvent.h"
#include "gwcEngine/Events/KeyEvent.h"
#include "gwcEngine/Events/MouseEvent.h"

//ECS
#include "gwcEngine/ECS/ECS.h"
//////////Components
#include"gwcEngine/ECS/Components/Mesh.h"
#include"gwcEngine/ECS/Components/Transform.h"

/////////systems
#include "gwcEngine//ECS/Systems/RendererECS.h"

//TODO, prevent double main inclusion.
// !!!!!!!!! Entry point !!!!!!
//#ifndef MAIN
//#define MAIN
//	#include "gwcEngine/Core/EntryPoint.h"
//#endif // !MAIN




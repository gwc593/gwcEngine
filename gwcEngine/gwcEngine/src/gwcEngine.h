#pragma once

#include"gepch.h"


//Core Functionality
#include"gwcEngine/Core/application.h"
#include "gwcEngine/Core/Log.h"
#include "gwcEngine/Core/Layer.h"
#include "gwcEngine/Core/Time.h"

//Input
#include "gwcEngine/Core/KeyCodes.h"
#include "gwcEngine/Core/MouseButtonCodes.h"
#include "gwcEngine/Core/Input.h"

//Rendering
#include "gwcEngine/Renderer/Renderer.h"
#include "gwcEngine/Renderer/RenderCommand.h"
#include "gwcEngine/Renderer/Material.h"
#include "gwcEngine/Renderer/FrameBuffer.h"
#include "gwcEngine/Renderer/Texture.h"
#include "gwcEngine/Renderer/Shader/Buffer.h"
#include "gwcEngine/Renderer/Shader/Shader.h"
#include "gwcEngine/Renderer/Shader/VertexArray.h"
#include "gwcEngine/Renderer/Cameras/OrthographicCamera.h"
#include "gwcEngine/Renderer/Cameras/PerspectiveCamera.h"

//Events System
#include "gwcEngine/Events/Event.h"

//ECS - Management
#include "gwcEngine/ECS/ECS.h"
//ECS - systems
#include "gwcEngine/ECS/Systems/RendererECS.h"

//Components
#include"gwcEngine/Components/Mesh.h"
#include"gwcEngine/Components/Transform.h"



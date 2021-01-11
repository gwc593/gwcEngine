#pragma once

#include"gepch.h"


//Core Functionality
#include"gwcEngine/Core/application.h"
#include "gwcEngine/Core/Log.h"
#include "gwcEngine/Core/Layer.h"
#include "gwcEngine/Core/Time.h"


//assest Management
#include "gwcEngine/AssetManagment/MeshLoader.h"
//Input
#include "gwcEngine/Core/KeyCodes.h"
#include "gwcEngine/Core/MouseButtonCodes.h"
#include "gwcEngine/Core/Input.h"


//Rendering
#include "gwcEngine/Renderer/Renderer.h"
#include "gwcEngine/Renderer/RenderLayer.h"
#include "gwcEngine/Renderer/RenderCommand.h"
#include "gwcEngine/Renderer/Material.h"
#include "gwcEngine/Renderer/FrameBuffer.h"
#include "gwcEngine/Renderer/Texture.h"
#include "gwcEngine/Renderer/Shader/Buffer.h"
#include "gwcEngine/Renderer/Shader/Shader.h"
#include "gwcEngine/Renderer/Shader/VertexArray.h"

//Components
#include "gwcEngine/Components/System/Cursor.h"
#include "gwcEngine/Components/System/Panel.h"

#include "gwcEngine/Components/Physics/Transform.h"
#include "gwcEngine/Components/Physics/Ray.h"
#include "gwcEngine/Components/Physics/Sphere.h"
#include "gwcEngine/Components/Physics/LifeTime.h"
#include "gwcEngine/Components/Physics/Collider.h"


#include "gwcEngine/Components/Render/Mesh.h"
#include "gwcEngine/Components/Render/MeshRenderer.h"
#include "gwcEngine/Components/Render/LineRenderer.h"

#include "gwcEngine/Components/Cameras/Camera.h"
#include "gwcEngine/Components/Cameras/OrthographicCamera.h"
#include "gwcEngine/Components/Cameras/PerspectiveCamera.h"

//Events System
#include "gwcEngine/Events/Event.h"

//ECS - Management
#include "gwcEngine/ECS/ECS.h"

//ECS - systems
#include "gwcEngine/ECS/Systems/CameraSystem.h"
#include "gwcEngine/ECS/Systems/MeshRenderingSystem.h"
#include "gwcEngine/ECS/Systems/LineRenderingSystem.h"
#include "gwcEngine/ECS/Systems/LifeTimeSystem.h"
#include "gwcEngine/ECS/Systems/MouseInteractionsSystem.h"



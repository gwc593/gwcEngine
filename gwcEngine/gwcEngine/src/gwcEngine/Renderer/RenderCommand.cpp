#include"gepch.h"
#include"RenderCommand.h"

#include"platform/OpenGL/OpenGLRendererAPI.h"
namespace gwcEngine
{
	//todo switch on context...
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
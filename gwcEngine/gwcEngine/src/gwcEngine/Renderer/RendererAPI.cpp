#include"gepch.h"
#include"RendererAPI.h"

namespace gwcEngine
{
	//Todo gwc - user set API, default should be none, currently hard coded to OpenGL
	//RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
}
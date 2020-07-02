#include "gepch.h"
#include"OpenGLTexture.h"
#include "stb_image.h"
#include <glad/glad.h>

namespace gwcEngine
{

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
//load texture image into memory
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		GE_CORE_ASSERT(data, "Texture image path {0} is not valid", path);

		m_Width = width;
		m_Height = height;
//upload texture image memory to the GPU
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		//todo - need to HDR and A
		//todo make channels exposed/automatic
		glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);

		//handle texture scaling 
		//todo make scaling choice dynamic (expose it to the API)
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 
							0, //mit map level
							0, 0, //partial texture upload
							m_Width, m_Height, //dimensions (smaller if partial)
							GL_RGBA, //format
                            GL_UNSIGNED_BYTE, //data type
							data); //pixle data pointer (loaded from stb_image)

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

}
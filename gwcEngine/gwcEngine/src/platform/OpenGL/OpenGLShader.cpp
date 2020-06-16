#include "gepch.h"
#include "OpenGLShader.h"

#include<glad/glad.h>
#include<glm//gtc/type_ptr.hpp>

namespace gwcEngine
{
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// Read our shaders into the appropriate buffers



		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave


			GE_CORE_ERROR("{0}", infoLog.data());
			GE_ASSERT(false, "Vertex shader failed to compile, see openGL log above...");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			GE_CORE_ERROR("{0}", infoLog.data());
			GE_ASSERT(false, "Fragment shader failed to compile, see openGL log above...");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_Renderer_ID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_Renderer_ID, vertexShader);
		glAttachShader(m_Renderer_ID, fragmentShader);

		// Link our program
		glLinkProgram(m_Renderer_ID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_Renderer_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(m_Renderer_ID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_Renderer_ID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_Renderer_ID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave

			GE_CORE_ERROR("{0}", infoLog.data());
			GE_ASSERT(false, "GLSL failed to link, see openGL log above...");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_Renderer_ID, vertexShader);
		glDetachShader(m_Renderer_ID, fragmentShader);
		ParseUniforms();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_Renderer_ID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_Renderer_ID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::ParseUniforms()
	{
		glUseProgram(m_Renderer_ID);
		int count = 0;
		int nameLen = -1;
		int num = -1;
		char name[100];
		GLenum type = GL_ZERO;
		ShaderDataType gwcType = ShaderDataType::None;

		glGetProgramiv(m_Renderer_ID, GL_ACTIVE_UNIFORMS, &count);
		for (int i = 0; i < count; i++) {
			glGetActiveUniform(m_Renderer_ID, (GLuint)i, sizeof(name) - 1, &nameLen, &num, &type, name);
			switch (type) {
			case GL_NONE:        gwcType = ShaderDataType::None; break;
			case GL_FLOAT:       gwcType = ShaderDataType::Float1;break;
			case GL_FLOAT_VEC2:  gwcType = ShaderDataType::Float2;break;
			case GL_FLOAT_VEC3:  gwcType = ShaderDataType::Float3;break;
			case GL_FLOAT_VEC4:  gwcType = ShaderDataType::Float4;break;
			case GL_FLOAT_MAT3:  gwcType = ShaderDataType::Mat3; break;
			case GL_FLOAT_MAT4:  gwcType = ShaderDataType::Mat4; break;
			case GL_INT:         gwcType = ShaderDataType::Int; break;
			case GL_INT_VEC2:    gwcType = ShaderDataType::Int2; break;
			case GL_INT_VEC3:    gwcType = ShaderDataType::Int3; break;
			case GL_INT_VEC4:    gwcType = ShaderDataType::Int4; break;
			case GL_BOOL:        gwcType = ShaderDataType::Bool; break;
			}
			m_Uniforms.push_back( ShaderUniform::Create(name,gwcType,this));
		}
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, const int& Int)
	{
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniform1i(location, Int);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const float& Float)
	{
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniform1f(location, Float);
	}

	void OpenGLShader::UploadUniformVec2(const std::string& name, const glm::vec3& vec2)
	{
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniform2f(location, vec2.x, vec2.y);
	}

	void OpenGLShader::UploadUniformVec3(const std::string& name, const glm::vec3& vec3)
	{
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniform3f(location, vec3.x, vec3.y, vec3.z);
	}

	void OpenGLShader::UploadUniformVec4(const std::string& name, const glm::vec4& vec4)
	{
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniform4f(location, vec4.r, vec4.g, vec4.b, vec4.a);
	}


	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	

}

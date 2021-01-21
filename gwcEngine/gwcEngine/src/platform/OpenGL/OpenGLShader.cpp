#include "gepch.h"
#include "OpenGLShader.h"
#include <fstream>



namespace gwcEngine
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment") return GL_FRAGMENT_SHADER;
		if (type == "pixel") return GL_FRAGMENT_SHADER;
		if (type == "geometry") return GL_GEOMETRY_SHADER;

		GE_CORE_ASSERT(false, "Unsupported shader type...");
		return GL_ZERO;
			
	}

	OpenGLShader::OpenGLShader(const std::string& shaderPath)
	{
		std::string shaderSource = FileSystem::GetInstance()->ReadToString(shaderPath);

		auto shaderElements = PreProcess(shaderSource);

		Compile(shaderElements);

		ParseUniforms();
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& shaderSource)
	{
		std::unordered_map<GLenum, std::string> shaderElements;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = shaderSource.find(typeToken, 0);

		while (pos != std::string::npos) 
		{
			size_t eol = shaderSource.find_first_of("\r\n", pos);
			GE_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = shaderSource.substr(begin, eol - begin);
			GE_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel" || type == "geometry", "Unsupported shader type specified, it has not been compiled...");

			size_t nextLinePos = shaderSource.find_first_not_of("\r\n", eol);
			pos = shaderSource.find(typeToken, nextLinePos);

			shaderElements[ShaderTypeFromString(type)] = shaderSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shaderSource.size() - 1: nextLinePos));
		}

		return shaderElements;
	}


	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderElements)
	{
		GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs(shaderElements.size());

		// Read our shaders into the appropriate buffers
		for (auto& kv : shaderElements) {
			GLenum shaderType = kv.first;
			const std::string& source = kv.second;

			GLuint Shader = glCreateShader(shaderType);

			const GLchar* sourceCstr = source.c_str();
			glShaderSource(Shader, 1, &sourceCstr, 0);

			glCompileShader(Shader);

			GLint isCompiled = 0;
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(Shader);

				GE_CORE_ERROR("{0}", infoLog.data());
				GE_ASSERT(false, "shader failed to compile, see openGL log above...");
				break;
			}
			glAttachShader(program, Shader);
			glShaderIDs.push_back(Shader);

		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.

			for (auto id : glShaderIDs) {
				glDeleteShader(id);
			}
			

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave

			GE_CORE_ERROR("{0}", infoLog.data());
			GE_ASSERT(false, "GLSL failed to link, see openGL log above...");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
		}


		m_Renderer_ID = program;
		ParseUniforms();
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> shaderElements;
		shaderElements[GL_VERTEX_SHADER] = vertexSrc;
		shaderElements[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(shaderElements);

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
		PROFILE_FUNCTION();
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
			case GL_FLOAT:       gwcType = ShaderDataType::Float;break;
			case GL_FLOAT_VEC2:  gwcType = ShaderDataType::Vec2;break;
			case GL_FLOAT_VEC3:  gwcType = ShaderDataType::Vec3;break;
			case GL_FLOAT_VEC4:  gwcType = ShaderDataType::Vec4;break;
			case GL_FLOAT_MAT3:  gwcType = ShaderDataType::Mat3; break;
			case GL_FLOAT_MAT4:  gwcType = ShaderDataType::Mat4; break;
			case GL_INT:         gwcType = ShaderDataType::Int; break;
			case GL_INT_VEC2:    gwcType = ShaderDataType::Int2; break;
			case GL_INT_VEC3:    gwcType = ShaderDataType::Int3; break;
			case GL_INT_VEC4:    gwcType = ShaderDataType::Int4; break;
			case GL_BOOL:        gwcType = ShaderDataType::Bool; break;
			case GL_SAMPLER_2D:  gwcType = ShaderDataType::Sampler2D; break;
			}
			m_Uniforms.push_back( ShaderUniform::Create(name,gwcType,this));
		}
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, const int& Int)
	{
		PROFILE_FUNCTION();
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniform1i(location, Int);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const float& Float)
	{
		PROFILE_FUNCTION();
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniform1f(location, Float);
	}

	void OpenGLShader::UploadUniformVec2(const std::string& name, const glm::vec2& vec2)
	{
		PROFILE_FUNCTION();
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniform2fv(location, 1, glm::value_ptr(vec2));
	}

	void OpenGLShader::UploadUniformVec3(const std::string& name, const glm::vec3& vec3)
	{
		PROFILE_FUNCTION();
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniform3fv(location, 1,glm::value_ptr(vec3));
	}

	void OpenGLShader::UploadUniformVec4(const std::string& name, const glm::vec4& vec4)
	{
		PROFILE_FUNCTION();
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(vec4));
	}


	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		PROFILE_FUNCTION();
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		PROFILE_FUNCTION();
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadTexture2D(const std::string& name, const Ref<Texture2D>& texture)
	{
		PROFILE_FUNCTION();
		glUseProgram(m_Renderer_ID);
		GLint location = glGetUniformLocation(m_Renderer_ID, name.c_str());
		texture->Bind();
	}

}

#include"gepch.h"
#include"Shader.h"

#include<glad/glad.h>
namespace gwcEngine
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
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
			GE_ASSERT(false,"Vertex shader failed to compile, see openGL log above...");
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
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_Renderer_ID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_Renderer_ID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}
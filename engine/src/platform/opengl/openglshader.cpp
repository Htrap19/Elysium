#include "openglshader.h"

#include "core/log.h"

#include <fstream>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Elysium
{
	namespace Util
	{
		static std::string ReadFile(const std::string& file)
		{
			std::ifstream in(file.c_str());
			if (!in)
			{
				ES_CORE_ERROR("Unable to open {0} file.", file);
				return "";
			}

			in.seekg(0, std::ios::end);
			auto size = in.tellg();
			if (size == -1)
			{
				ES_CORE_ERROR("Unable to read {0} file.", file);
				return "";
			}

			in.seekg(0, std::ios::beg);
			std::string result;
			result.resize(size);
			in.read(result.data(), (std::streamsize)result.size());

			return result;
		}

		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
				return GL_VERTEX_SHADER;
			else if (type == "geometry")
				return GL_GEOMETRY_SHADER;
			else if (type == "fragment")
				return GL_FRAGMENT_SHADER;

			return 0;
		}
	}

	OpenGLShader::OpenGLShader(const std::string& shaderFile)
	{
		auto source = Util::ReadFile(shaderFile);
		auto shaderSources = PreProcess(source);
		CompileShader(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ProgramId);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ProgramId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniformi(const std::string& name, int32_t value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniformf(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniformVec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetUniformVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetUniformVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetUniformMat3(const std::string& name, const glm::mat3& value)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	OpenGLShader::MapType OpenGLShader::PreProcess(const std::string& source)
	{
		MapType shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = std::strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eo1 = source.find_first_of("\r\n", pos);
			if (eo1 == std::string::npos)
			{
				ES_CORE_ERROR("Syntax error!");
				break;
			}
			size_t begin = pos + (typeTokenLength + 1);
			std::string type = source.substr(begin, eo1 - begin);
			if (!Util::ShaderTypeFromString(type))
			{
				ES_CORE_ERROR("Invalid shader type specified!");
				break;
			}

			size_t nextLinePos = source.find_first_not_of("\r\n", eo1);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[type] = source.substr(nextLinePos, (pos - (nextLinePos == std::string::npos ? 
																		source.size() - 1 : 
																		nextLinePos)));
		}

		return shaderSources;
	}
	
	void OpenGLShader::CompileShader(const MapType& shaderSources)
	{
		m_ProgramId = glCreateProgram();
		if (!m_ProgramId)
		{
			ES_CORE_CRITICAL("Unable to create shader program");
			return;
		}

		GLint result = 0;
		GLchar eLog[1024] = { 0 };
		GLint* shaders = (GLint*)alloca(shaderSources.size() * sizeof(GLint));
		uint32_t shaderCount = 0;
		for (auto& [type, source] : shaderSources)
		{
			auto shader = glCreateShader(Util::ShaderTypeFromString(type));
			const GLchar* code[1] = { source.c_str() };
			const GLint codeLength[1] = { (GLint)source.size() };
			glShaderSource(shader, 1, code, codeLength);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				glGetShaderInfoLog(shader, sizeof(eLog), nullptr, eLog);
				ES_CORE_ERROR("Failed to compile {0} shader: {1}", type.c_str(), eLog);
				glDeleteShader(shader);
				continue;
			}

			glAttachShader(m_ProgramId, shader);
			shaders[shaderCount] = shader;
			shaderCount++;
		}

		glLinkProgram(m_ProgramId);

		for (uint32_t i = 0; i < shaderCount; i++)
		{
			glDetachShader(m_ProgramId, shaders[i]);
			glDeleteShader(shaders[i]);
		}

		glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			glGetProgramInfoLog(m_ProgramId, sizeof(eLog), nullptr, eLog);
			ES_CORE_ERROR("Failed to link program: {0}", eLog);
			glDeleteProgram(m_ProgramId);
		}
	}

	int32_t OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformCache.contains(name))
		{
			return m_UniformCache[name];
		}

		auto location = glGetUniformLocation(m_ProgramId, name.c_str());
		m_UniformCache[name] = location;
		return location;
	}
}
#pragma once

#include "renderer/shader.h"

#include <unordered_map>

namespace Elysium
{
	class OpenGLShader : public Shader
	{
	public:
		using MapType = std::unordered_map<std::string, std::string>;
		using UniformCacheType = std::unordered_map<std::string, int32_t>;

	public:
		OpenGLShader(const std::string& shaderFile);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniformi(const std::string& name, int32_t value) override;
		virtual void SetUniformf(const std::string& name, float value) override;
		virtual void SetUniformVec2(const std::string& name, const glm::vec2& value) override;
		virtual void SetUniformVec3(const std::string& name, const glm::vec3& value) override;
		virtual void SetUniformVec4(const std::string& name, const glm::vec4& value) override;
		virtual void SetUniformMat3(const std::string& name, const glm::mat3& value) override;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) override;

	private:
		MapType PreProcess(const std::string& source);
		void CompileShader(const MapType& shaderSources);
		int32_t GetUniformLocation(const std::string& name);

	private:
		uint32_t m_ProgramId = 0;
		UniformCacheType m_UniformCache;
	};
}
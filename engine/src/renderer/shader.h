#pragma once

#include "core/utility.h"

#include <string>

#include <glm/glm.hpp>

namespace Elysium
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniformi(const std::string& name, int32_t value) = 0;
		virtual void SetUniformf(const std::string& name, float value) = 0;
		virtual void SetUniformVec2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetUniformVec3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetUniformVec4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetUniformMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) = 0;

		static Shared<Shader> Create(const std::string& shaderFile);
	};
}
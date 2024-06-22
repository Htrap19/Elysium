#pragma once

#include "core/utility.h"

#include "renderer/vertexarray.h"
#include "renderer/shader.h"

#include <glm/glm.hpp>

namespace Elysium
{
	class RendererAPI
	{
	public:
		enum class Api
		{
			None = 0,
			OpenGL
		};

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x,
								 uint32_t y,
								 uint32_t width,
								 uint32_t height) = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void DrawIndexed(const Shared<VertexArray>& vertexArray,
								 uint32_t indexCount = 0) = 0;

		static Api GetApi() { return s_Api; };
		static Unique<RendererAPI> Create();

	private:
		static Api s_Api;
	};
}
#pragma once

#include "renderer/rendererapi.h"

namespace Elysium
{
	class RenderCommand
	{
	public:
		static void Init() { s_RendererAPI->Init(); }
		static void SetViewport(uint32_t x,
								uint32_t y,
								uint32_t width,
								uint32_t height)
		{ s_RendererAPI->SetViewport(x, y, width, height); }
		static void Clear() { s_RendererAPI->Clear(); }
		static void SetClearColor(const glm::vec4& color)
		{ s_RendererAPI->SetClearColor(color); }

	private:
		static Unique<RendererAPI> s_RendererAPI;
	};
}
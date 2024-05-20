#pragma once

#include <glm/glm.hpp>

namespace Elysium
{
	class Renderer
	{
	public:
		static void Clear();
		static void ClearColor(const glm::vec4& color);
	};
}
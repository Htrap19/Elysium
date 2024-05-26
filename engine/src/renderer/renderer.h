#pragma once

#include "renderer/vertexarray.h"
#include "renderer/shader.h"

#include <glm/glm.hpp>

namespace Elysium
{
	class Renderer
	{
	public:
		static void Init();
		static void Draw(const Shared<VertexArray>& vertexArray,
						 const Shared<Shader>& shader);
	};
}
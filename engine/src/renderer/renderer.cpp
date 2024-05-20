#include "renderer.h"

#include <glad/glad.h>

namespace Elysium
{
	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
}

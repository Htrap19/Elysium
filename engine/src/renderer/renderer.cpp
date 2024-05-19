#include "renderer.h"

#include <glad/glad.h>

namespace Elysium
{
	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::ClearColor()
	{
		glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
	}
}

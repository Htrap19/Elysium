#include "renderer.h"

#include <glad/glad.h>

namespace Elysium
{
	void Renderer::Init()
	{
	}

	void Renderer::Draw(const Shared<VertexArray>& vertexArray,
						const Shared<Shader>& shader)
	{
		vertexArray->Bind();
		shader->Bind();

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

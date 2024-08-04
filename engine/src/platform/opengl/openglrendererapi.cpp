#include "openglrendererapi.h"

#include <glad/glad.h>

namespace Elysium
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::DrawIndexed(const Shared<VertexArray>& vertexArray,
										uint32_t indexCount)
	{
		auto count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();

		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, (GLsizei)count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawLinesIndexed(const Shared<VertexArray>& vertexArray,
											 uint32_t indexCount)
	{
		auto count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		
		vertexArray->Bind();
		glDrawElements(GL_LINES, (GLsizei)count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SetDepthMask(bool enable)
	{
		glDepthMask(enable ? GL_TRUE : GL_FALSE);
	}
}

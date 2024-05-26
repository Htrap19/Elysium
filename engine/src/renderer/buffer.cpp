#include "buffer.h"

#include "core/log.h"

#include "renderer/rendererapi.h"

#include "platform/opengl/openglbuffer.h"

namespace Elysium
{
	Shared<VertexBuffer> VertexBuffer::Create(size_t size,
											  const void* data)
	{
		switch (RendererAPI::GetApi())
		{
		case RendererAPI::Api::None:
			ES_CORE_CRITICAL("Vertex buffer none detected!");
			break;
		case RendererAPI::Api::OpenGL:
			return MakeShared<OpenGLVertexBuffer>(size, data);

		default:
			break;
		}

		return nullptr;
	}

	Shared<IndexBuffer> IndexBuffer::Create(uint32_t count,
											const uint32_t* data)
	{
		switch (RendererAPI::GetApi())
		{
		case RendererAPI::Api::None:
			ES_CORE_CRITICAL("Vertex buffer none detected!");
			break;
		case RendererAPI::Api::OpenGL:
			return MakeShared<OpenGLIndexBuffer>(count, data);

		default:
			break;
		}

		return nullptr;
	}
}
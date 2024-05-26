#include "vertexarray.h"

#include "core/log.h"

#include "renderer/rendererapi.h"

#include "platform/opengl/openglvertexarray.h"

namespace Elysium
{
	Shared<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetApi())
		{
		case RendererAPI::Api::None:
			ES_CORE_CRITICAL("RendererAPI none detected!");
			break;
		case RendererAPI::Api::OpenGL:
			return MakeShared<OpenGLVertexArray>();

		default:
			break;
		}

		return nullptr;
	}
}
#include "rendererapi.h"

#include "core/log.h"

#include "platform/opengl/openglrendererapi.h"

namespace Elysium
{
	RendererAPI::Api RendererAPI::s_Api = RendererAPI::Api::OpenGL;

	Unique<RendererAPI> RendererAPI::Create()
	{
		switch (RendererAPI::s_Api)
		{
		case RendererAPI::Api::None:
			ES_CORE_CRITICAL("Renderer API none detected!");
			break;
		case RendererAPI::Api::OpenGL:
			return MakeUnique<OpenGLRendererAPI>();

		default:
			break;
		}

		return nullptr;
	}
}

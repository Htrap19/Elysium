#include "graphicscontext.h"

#include "core/log.h"

#include "renderer/rendercommand.h"

#include "platform/opengl/openglcontext.h"

namespace Elysium
{
	Unique<GraphicsContext> GraphicsContext::Create(GLFWwindow* window)
	{
		switch (RendererAPI::GetApi())
		{
		case RendererAPI::Api::None:
			ES_CORE_CRITICAL("Graphics Context none detected!");
			break;
		case RendererAPI::Api::OpenGL:
			return MakeUnique<OpenGLContext>(window);

		default:
			break;
		}
		
		return nullptr;
	}
}

#include "framebuffer.h"

#include "core/log.h"

#include "renderer/rendererapi.h"

#include "platform/opengl/openglframebuffer.h"

namespace Elysium
{
	Shared<FrameBuffer> FrameBuffer::Create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetApi())
		{
		case RendererAPI::Api::None:
			ES_CORE_CRITICAL("RendererAPI none detected!");
			break;
		case RendererAPI::Api::OpenGL:
			return MakeShared<OpenGLFrameBuffer>(width, height);

		default:
			break;
		}

		return nullptr;
	}
}
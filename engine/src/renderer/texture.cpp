#include "texture.h"

#include "core/log.h"

#include "renderer/rendererapi.h"

#include "platform/opengl/opengltexture.h"

namespace Elysium
{
	Shared<Texture2D> Texture2D::Create(const std::string& imgFile, bool flip)
	{
		switch (RendererAPI::GetApi())
		{
		case RendererAPI::Api::None:
			ES_CORE_CRITICAL("RendererAPI none detected!");
			break;
		case RendererAPI::Api::OpenGL:
			return MakeShared<OpenGLTexture2D>(imgFile, flip);

		default:
			break;
		}

		return nullptr;
	}

	Shared<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetApi())
		{
		case RendererAPI::Api::None:
			ES_CORE_CRITICAL("RendererAPI none detected!");
			break;
		case RendererAPI::Api::OpenGL:
			return MakeShared<OpenGLTexture2D>(width, height);

		default:
			break;
		}

		return nullptr;
	}

	Shared<CubeMap> CubeMap::Create(const std::array<std::string, 6> faces)
	{
		switch (RendererAPI::GetApi())
		{
		case RendererAPI::Api::None:
			ES_CORE_CRITICAL("RendererAPI none detected!");
			break;
		case RendererAPI::Api::OpenGL:
			return MakeShared<OpenGLCubeMap>(faces);

		default:
			break;
		}

		return nullptr;
	}
}
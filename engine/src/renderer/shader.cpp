#include "shader.h"

#include "core/log.h"

#include "renderer/rendererapi.h"

#include "platform/opengl/openglshader.h"

namespace Elysium
{
	Shared<Shader> Shader::Create(const std::string& shaderFile)
	{
		switch (RendererAPI::GetApi())
		{
		case RendererAPI::Api::None:
			ES_CORE_CRITICAL("RendererAPI none detected!");
			break;
		case RendererAPI::Api::OpenGL:
			return MakeShared<OpenGLShader>(shaderFile);

		default:
			break;
		}

		return nullptr;
	}
}

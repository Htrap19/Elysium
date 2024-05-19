#include "graphicscontext.h"

#include "platform/opengl/openglcontext.h"

namespace Elysium
{
	Unique<GraphicsContext> GraphicsContext::Create(GLFWwindow* window)
	{
		return MakeUnique<OpenGLContext>(window);
	}
}

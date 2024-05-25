#include "rendercommand.h"

namespace Elysium
{
	Unique<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
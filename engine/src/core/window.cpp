#include "window.h"

#ifdef ES_PLATFORM_WINDOWS
#include "platform/windows/windowswindow.h"
#endif

namespace Elysium
{
	Unique<Window> Window::Create(const WindowProps& props)
	{
#ifdef ES_PLATFORM_WINDOWS
		return MakeUnique<WindowsWindow>(props);
#endif
		return nullptr;
	}
}

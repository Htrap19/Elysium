#include "window.h"

#ifdef ES_PLATFORM_WINDOWS
#include "platform/windows/windowswindow.h"
#elif defined ES_PLATFORM_UNIX
#include "platform/x11/x11window.h"
#endif

namespace Elysium
{
	Unique<Window> Window::Create(const WindowProps& props)
	{
#ifdef ES_PLATFORM_WINDOWS
        return MakeUnique<WindowsWindow>(props);
#elif defined ES_PLATFORM_UNIX
        return MakeUnique<UnixWindow>(props);
#endif
		return nullptr;
	}
}

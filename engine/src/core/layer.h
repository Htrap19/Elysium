#pragma once

#include "event/event.h"

namespace Elysium
{
	class Layer
	{
	public:
		virtual void OnAttach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender() {}
		virtual void OnDetach() {}
	};
}
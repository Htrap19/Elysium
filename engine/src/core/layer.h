#pragma once

#include "event/event.h"

#include "core/timestep.h"

namespace Elysium
{
	class Layer
	{
	public:
		virtual void OnAttach() {}
		virtual void OnUpdate(Timestep timeStep) {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender() {}
		virtual void OnDetach() {}
	};
}
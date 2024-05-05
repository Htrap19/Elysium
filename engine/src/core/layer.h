#pragma once

namespace Elysium
{
	class Layer
	{
	public:
		virtual void OnAttach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnDetach() {}
	};
}
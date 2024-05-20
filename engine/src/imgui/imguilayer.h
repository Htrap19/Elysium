#pragma once

#include "core/layer.h"

namespace Elysium
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer() = default;
		virtual ~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	};
}
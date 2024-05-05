#pragma once

#include "utility.h"
#include "layerstack.h"

namespace Elysium
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Push(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();

	private:
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

	Elysium::Unique<Elysium::Application> CreateApplication();
}
#pragma once

#include "utility.h"
#include "layerstack.h"
#include "window.h"

#include "event/applicationevent.h"

namespace Elysium
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void OnEvent(Event& e);

		void Push(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		LayerStack m_LayerStack;
		bool m_Running = true;
		Unique<Window> m_Window;
	};

	Elysium::Unique<Elysium::Application> CreateApplication();
}
#include "application.h"
#include "log.h"

#include "event/event.h"
#include "renderer/renderer.h"

namespace Elysium
{
	Application::Application()
	{
		m_Window = Window::Create();
		m_Window->SetEventCallback(ES_BIND_EVENT_FN(Application::OnEvent));
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ES_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(ES_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Push(Layer* layer)
	{
		m_LayerStack.Push(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Renderer::Clear();
			Renderer::ClearColor();

			for (auto layer : m_LayerStack)
				layer->OnUpdate();

			for (auto layer : m_LayerStack)
				layer->OnImGuiRender();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return false;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		ES_CORE_INFO(e.ToString());
		return false;
	}

	extern Elysium::Unique<Elysium::Application> CreateApplication();
}

int main(int argc, char* argv[])
{
	Elysium::Log::Init();
	auto app = Elysium::CreateApplication();
	app->Run();

	return 0;
}
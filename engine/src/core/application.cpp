#include "application.h"

#include "core/log.h"
#include "core/timestep.h"

#include "event/event.h"

#include "renderer/rendercommand.h"
#include "renderer/renderer.h"

#include <GLFW/glfw3.h>

namespace Elysium
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		if (s_Instance)
		{
			ES_CORE_CRITICAL("Application already exists!");
			return;
		}

		s_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(ES_BIND_EVENT_FN(Application::OnEvent));

		RenderCommand::Init();
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
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
		double time = 0.0f;
		while (m_Running)
		{
			time = glfwGetTime();
			Timestep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			
			RenderCommand::Clear();

			for (auto layer : m_LayerStack)
				layer->OnUpdate(timeStep);

			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	Application& Application::GetInstance()
	{
		return *s_Instance;
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
#include "application.h"
#include "log.h"

namespace Elysium
{
	Application::Application()
	{
		ES_CORE_INFO("Application created!");
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
			for (auto layer : m_LayerStack)
				layer->OnUpdate();

			for (auto layer : m_LayerStack)
				layer->OnImGuiRender();
		}
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
#include "engine.h"
#include "core/application.h"

#include <imgui.h>
#include <glm/glm.hpp>

class SandboxLayer : public Elysium::Layer
{
public:
	virtual void OnAttach() override
	{
		ES_INFO("Sandbox layer attached!");
	}

	virtual void OnEvent(Elysium::Event& e) override
	{
		Elysium::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Elysium::KeyTypedEvent>([](Elysium::KeyTypedEvent& e)
			{
				ES_TRACE(e.ToString());
				return false;
			});
	}

	virtual void OnUpdate() override
	{
		Elysium::Renderer::ClearColor(m_backgroundColor);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Window");

		ImGui::Text("Hello world!");
		ImGui::ColorEdit4("Pick background", &m_backgroundColor[0]);

		ImGui::End();

		ImGui::Begin("Example");

		ImGui::Text("Click me");

		ImGui::End();
	}

private:
	glm::vec4 m_backgroundColor = { 0.3f, 0.3f, 0.5f, 1.0f };
};

class SandboxApplication : public Elysium::Application
{
public:
	SandboxApplication()
	{
		Push(new SandboxLayer);
	}
};

Elysium::Unique<Elysium::Application> Elysium::CreateApplication()
{
	return Elysium::MakeUnique<SandboxApplication>();
}
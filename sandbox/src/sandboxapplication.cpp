#include "engine.h"
#include "core/application.h"

class SandboxLayer : public Elysium::Layer
{
public:
	virtual void OnAttach() override
	{
		ES_INFO("Sandbox layer attached!");
	}

	virtual void OnEvent(Elysium::Event& e)
	{
		Elysium::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Elysium::KeyTypedEvent>([](Elysium::KeyTypedEvent& e)
			{
				ES_TRACE(e.ToString());
				return false;
			});
	}
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
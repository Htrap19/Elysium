#include "engine.h"
#include "core/application.h"

class SandboxLayer : public Elysium::Layer
{
public:
	virtual void OnAttach() override
	{
		ES_INFO("Sandbox layer attached!");
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
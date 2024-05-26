#include "core/application.h"

#include "sandboxlayer.h"

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
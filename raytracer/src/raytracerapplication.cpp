#include "core/application.h"

#include "raytracerlayer.h"

class RayTracerApplication : public Elysium::Application
{
public:
    RayTracerApplication()
	{
        Push(new RayTracerLayer);
	}
};

Elysium::Unique<Elysium::Application> Elysium::CreateApplication()
{
    return Elysium::MakeUnique<RayTracerApplication>();
}

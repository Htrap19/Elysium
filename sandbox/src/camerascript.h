#pragma once

#include "wasdcontroller.h"
#include "translation.h"

class CameraScript : public CameraTranslation, public WASDController
{
public:

protected:
	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		CameraTranslation::OnUpdate(ts);
		WASDController::OnUpdate(ts);
	}
};
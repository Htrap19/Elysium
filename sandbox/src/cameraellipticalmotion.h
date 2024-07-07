#pragma once

#include "ellipticalmotion.h"

class CameraEllipticalMotion : public EllipticalMotion
{
public:
	CameraEllipticalMotion() = default;

protected:
	virtual void OnCreate() override
	{
		SetPlaying(true);
	}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		if (!IsPlaying())
			return;

		auto velocity = ts * GetMovementSpeed();
		SetTheta(GetTheta() + velocity);

		if (GetTheta() > 359.0f)
			SetTheta(0.0f);

		auto& cc = m_Self.GetComponent<Elysium::CameraComponent>();
		cc.Camera.SetPosition(CalculatePosition());
		cc.Camera.SetFront(GetCenter() - cc.Camera.GetPosition());
	}
};
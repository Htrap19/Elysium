#pragma once

#include "engine.h"

class WASDController : public Elysium::ScriptableEntity
{
public:
	WASDController() = default;

	inline void SetEnabled(bool enabled)
	{ m_Enabled = enabled; }

protected:
	virtual void OnCreate() override
	{
		/*if (!m_Self.HasComponent<Elysium::CameraComponent>())
		{
			ES_ERROR("WASD controller added without CameraComponent!.");
			ES_INFO("Adding CameraComponent will eliminate this issue.");
		}*/
	}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		if (!m_Self.HasComponent<Elysium::CameraComponent>() || 
			!m_Enabled)
			return;

		auto& cc = m_Self.GetComponent<Elysium::CameraComponent>();
        if (cc.CameraIns.GetAspectRatio() != m_Self.GetScene()->GetAspectRatio())
            cc.CameraIns.SetAspectRatio(m_Self.GetScene()->GetAspectRatio());

		if (Elysium::Input::IsKeyPressed(Elysium::Key::W))
            cc.CameraIns.MoveForward(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::S))
            cc.CameraIns.MoveBackward(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::A))
            cc.CameraIns.MoveLeft(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::D))
            cc.CameraIns.MoveRight(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::Space))
            cc.CameraIns.MoveUp(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::LeftShift))
            cc.CameraIns.MoveDown(ts);

		auto cursor = Elysium::Input::GetCursorPosition();
		m_DeltaX = cursor.x - m_LastX;
		m_DeltaY = m_LastY - cursor.y;

		m_LastX = cursor.x;
		m_LastY = cursor.y;

        cc.CameraIns.MoveCursor(m_DeltaX, m_DeltaY);
	}

	virtual void OnDestroy() override
	{}

private:
	bool m_Enabled = false;
	float m_LastX = 0.0f, m_LastY = 0.0f;
	float m_DeltaX = 0.0f, m_DeltaY = 0.0f;
};

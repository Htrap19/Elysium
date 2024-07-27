#pragma once

#include "engine.h"

class WASDController : public virtual Elysium::ScriptableEntity
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
		if (cc.Camera.GetAspectRatio() != m_Self.GetScene()->GetAspectRatio())
			cc.Camera.SetAspectRatio(m_Self.GetScene()->GetAspectRatio());

		if (Elysium::Input::IsKeyPressed(Elysium::Key::W))
			cc.Camera.MoveForward(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::S))
			cc.Camera.MoveBackward(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::A))
			cc.Camera.MoveLeft(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::D))
			cc.Camera.MoveRight(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::Space))
			cc.Camera.MoveUp(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::LeftShift))
			cc.Camera.MoveDown(ts);

		auto cursor = Elysium::Input::GetCursorPosition();
		m_DeltaX = cursor.x - m_LastX;
		m_DeltaY = m_LastY - cursor.y;

		m_LastX = cursor.x;
		m_LastY = cursor.y;

		cc.Camera.MoveCursor(m_DeltaX, m_DeltaY);
	}

	virtual void OnDestroy() override
	{}

private:
	bool m_Enabled = false;
	float m_LastX = 0.0f, m_LastY = 0.0f;
	float m_DeltaX = 0.0f, m_DeltaY = 0.0f;
};
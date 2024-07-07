#pragma once

#include "engine.h"

class EllipticalMotion : public Elysium::ScriptableEntity
{
public:
	EllipticalMotion() = default;

	inline void SetPlaying(bool playing)
	{ m_Playing = playing; }

protected:
	virtual void OnCreate() override
	{}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		if (!m_Playing)
			return;

		auto velocity = ts * m_MovementSpeed;
		m_T += velocity;

		if (m_T >= 359.0f)
			m_T = 0.0f;

		float x = m_SemiMajor * cos(m_T);
		float y = m_SemiMinor * sin(m_T);

		auto& tc = m_Self.GetComponent<Elysium::TransformComponent>();
		tc.Position.x = x;
		tc.Position.y = y;
	}

	virtual void OnDestroy() override
	{}

private:
	float m_SemiMajor = 11.18f; // half the longest diameter
	float m_SemiMinor = 5.0f;	// half the shortest diameter
	float m_T = 90.0f;			// varies from 0 to 359 (0 to 2 pi)

	float m_MovementSpeed = 1.5f;

	bool m_Playing = true;
};
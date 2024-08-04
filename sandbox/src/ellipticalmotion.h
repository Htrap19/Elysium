#pragma once

#include "engine.h"

class EllipticalMotion : public Elysium::ScriptableEntity
{
public:
	EllipticalMotion() = default;

	inline void SetPlaying(bool playing)
	{ m_Playing = playing; }

	inline bool IsPlaying() const
	{ return m_Playing; }

	inline void SetCenter(const glm::vec3& center)
	{ m_Center = center; }

	inline const glm::vec3& GetCenter() const
	{ return m_Center; }

	inline void SetMovementSpeed(float speed)
	{ m_MovementSpeed = speed; }

	inline float GetMovementSpeed() const
	{ return m_MovementSpeed; }

	inline void SetTheta(float theta)
	{ m_Theta = theta; }

	inline float GetTheta() const
	{ return m_Theta; }

	inline void SetPhi(float phi)
	{ m_Phi = phi; }

	inline float GetPhi() const
	{ return m_Phi; }

	inline void SetA(float a)
	{ m_A = a; }

	inline float GetA() const
	{ return m_A; }

	inline void SetB(float b)
	{ m_B = b; }

	inline float GetB() const
	{ return m_B; }

	inline void SetC(float c)
	{ m_C = c; }

	inline float GetC() const
	{ return m_C; }

protected:
	glm::vec3 CalculatePosition() const
	{
		float x = m_A * sin(glm::radians(m_Theta)) * cos(glm::radians(m_Phi));
		float y = m_B * sin(glm::radians(m_Theta)) * sin(glm::radians(m_Phi));
		float z = m_C * cos(glm::radians(m_Theta));
		/*float x = m_A * cos(m_Theta);
		float y = m_B * sin(m_Theta) * cos(m_Phi);
		float z = m_C * sin(m_Theta) * sin(m_Phi);*/

		return m_Center + glm::vec3{ x, y, z };
	}

	virtual void OnCreate() override
	{}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		if (!m_Playing)
			return;

		auto velocity = ts * m_MovementSpeed;
		m_Theta += velocity;

		if (m_Theta > 359.0f)
			m_Theta = 0.0f;

		auto& tc = m_Self.GetComponent<Elysium::TransformComponent>();
		tc.Position = CalculatePosition();
	}

	virtual void OnDestroy() override
	{}

private:
	float m_A = 50.0f;  // half the longest diameter
	float m_B = 50.0f;	// half the shortest diameter
	float m_C = 50.0f;	// half the diameter for Z axis

	float m_Theta = 0.0f;	// varies from 0 to 359 (0 to 2 pi)
	float m_Phi = 0.0f;	// the angle from the z-axis

	float m_MovementSpeed = 0.5f;

	glm::vec3 m_Center = glm::vec3(0.0f);

	bool m_Playing = false;
};
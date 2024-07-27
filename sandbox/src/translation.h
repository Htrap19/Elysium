#pragma once

#include "engine.h"

class CameraTranslation : public virtual Elysium::ScriptableEntity
{
public:
	/*inline void SetTargetPosition(const glm::vec3& targetPosition)
	{ m_TargetPosition = targetPosition, m_IsTranstioning = true; }

	inline void SetTransitionSpeed(float speed)
	{ m_TransitionSpeed = speed; }*/

	inline void TranslateTo(const glm::vec3& pos, float t)
	{
		auto& cc = m_Self.GetComponent<Elysium::CameraComponent>();
		m_StartPosition = cc.Camera.GetPosition();
		m_EndPosition = pos;
		m_TotalTime = t;
		m_TotalDistance = glm::distance(m_EndPosition, m_StartPosition);
		m_CurrentTime = 0.0f;
		m_Direction = glm::normalize(m_EndPosition - m_StartPosition);
	}

protected:
	float EaseInOut(float t) const
	{
		return t * t * (3.0f - 2.0f * t);
	}

	float SmoothStep(float t)
	{
		float scaledT = EaseInOut(t);
		return scaledT * scaledT * (3.0f - 2.0f * scaledT);
	}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		if (m_CurrentTime >= m_TotalTime)
			return;

		m_CurrentTime = std::min(m_CurrentTime + ts.GetSeconds(), m_TotalTime);

		float t = m_CurrentTime / m_TotalTime;
		float smoothT = SmoothStep(t);

		auto& cc = m_Self.GetComponent<Elysium::CameraComponent>();
		cc.Camera.SetPosition(m_StartPosition + (m_EndPosition - m_StartPosition) * smoothT);
		cc.Camera.SetFront(m_Direction);
	}

private:
	glm::vec3 m_StartPosition = glm::vec3(0.0f);
	glm::vec3 m_EndPosition = glm::vec3(0.0f);
	glm::vec3 m_Direction = glm::vec3(0.0f);
	float m_TotalTime = 0.0f;
	float m_CurrentTime = 0.0f;
	float m_TotalDistance = 0.0f;
};
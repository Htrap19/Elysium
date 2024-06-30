#pragma once

#include "core/timestep.h"

#include <glm/glm.hpp>

namespace Elysium
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::vec3& position,
			   float yaw,
			   float pitch,
			   float movementSpeed,
			   float turningSpeed);

		void MoveForward(Timestep ts);
		void MoveBackward(Timestep ts);
		void MoveLeft(Timestep ts);
		void MoveRight(Timestep ts);
		void MoveUp(Timestep ts);
		void MoveDown(Timestep ts);

		void MoveCursor(float deltaX,
						float deltaY);

		glm::mat4 CalculateView() const;

		inline void SetPosition(const glm::vec3& position)
		{ m_Position = position; }

		inline const glm::vec3& GetPosition() const
		{ return m_Position; }

		inline void SetFront(const glm::vec3& front)
		{ m_Front = front; }

		inline const glm::vec3& GetFront() const
		{ return m_Front; }

		inline void SetYaw(float yaw)
		{ m_Yaw = yaw; }

		inline float GetYaw() const
		{ return m_Yaw; }

		inline void SetPitch(float pitch)
		{ m_Pitch = pitch; }

		inline float GetPitch() const
		{ return m_Pitch; }

		inline void SetTurningSpeed(float speed)
		{ m_TurningSpeed = speed; }

		inline float GetTurningSpeed() const
		{ return m_TurningSpeed; }

		inline void SetMovementSpeed(float speed)
		{ m_MovementSpeed = speed; }

		inline float GetMovementSpeed() const
		{ return m_MovementSpeed; }

	private:
		void Update();

	private:
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Front = { 0.0f, 0.0f, 1.0f };
		glm::vec3 m_Right = glm::vec3(0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f);
		float m_Yaw = -90.0f, m_Pitch = 0.0f;
		float m_TurningSpeed = 5.0f;
		float m_MovementSpeed = 0.0f;
	};
}
#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

namespace Elysium
{
	static const glm::vec3 s_WorldUp = { 0.0f, 1.0f, 0.0f };

	Camera::Camera(const glm::vec3& position,
				   float yaw,
				   float pitch,
				   float movementSpeed,
				   float turningSpeed)
		: m_Position(position),
		m_Yaw(yaw),
		m_Pitch(pitch),
		m_TurningSpeed(turningSpeed),
		m_MovementSpeed(movementSpeed)
	{
		Update();
	}

	void Camera::MoveForward(Timestep ts)
	{
		auto velocity = ts * m_MovementSpeed;
		m_Position += m_Front * velocity;
		Update();
	}

	void Camera::MoveBackward(Timestep ts)
	{
		auto velocity = ts * m_MovementSpeed;
		m_Position -= m_Front * velocity;
		Update();
	}

	void Camera::MoveLeft(Timestep ts)
	{
		auto velocity = ts * m_MovementSpeed;
		m_Position -= m_Right * velocity;
		Update();
	}

	void Camera::MoveRight(Timestep ts)
	{
		auto velocity = ts * m_MovementSpeed;
		m_Position += m_Right * velocity;
		Update();
	}

	void Camera::MoveUp(Timestep ts)
	{
		auto velocity = ts * m_MovementSpeed;
		m_Position += s_WorldUp * velocity;
		Update();
	}

	void Camera::MoveDown(Timestep ts)
	{
		auto velocity = ts * m_MovementSpeed;
		m_Position -= s_WorldUp * velocity;
		Update();
	}

	void Camera::MoveCursor(float deltaX,
							float deltaY)
	{
		m_Yaw += deltaX * m_TurningSpeed;
		m_Pitch += deltaY * m_TurningSpeed;

		m_Pitch = std::clamp(m_Pitch, -89.0f, 89.0f);

		Update();
	}

	glm::mat4 Camera::CalculateView() const
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	glm::mat4 Camera::CalculateProjection() const
	{
		return glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
	}

	void Camera::Update()
	{
		m_Front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
		m_Front.y = sin(glm::radians(m_Pitch));
		m_Front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
		m_Front = glm::normalize(m_Front);

		m_Right = glm::normalize(glm::cross(m_Front, s_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}
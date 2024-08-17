#ifndef CAMERA_H
#define CAMERA_H

#include "engine.h"

#include <glm/glm.hpp>

#include <vector>

class Camera
{
public:
    Camera(float verticalFOV, float nearClip, float farClip);

    void OnResize(uint32_t width, uint32_t height);
    void OnUpdate(Elysium::Timestep ts);

    const glm::mat4& GetProjection() const { return m_Projection; }
    const glm::mat4& GetInverseProjection() const { return m_InverseProjection; }
    const glm::mat4& GetView() const { return m_View; }
    const glm::mat4& GetInverseView() const { return m_InverseView; }

    const glm::vec3& GetPosition() const { return m_Position; }
    const glm::vec3& GetDirection() const { return m_ForwardDirection; }

    float GetRotationSpeed() const;

    const std::vector<glm::vec3>& GetRayDirections() const { return m_RayDirections; }

private:
    void RecalculateProjection();
    void RecalculateView();
    void RecalculateRayDirections();

private:
    glm::mat4 m_Projection = glm::mat4(1.0f);
    glm::mat4 m_InverseProjection = glm::mat4(1.0f);
    glm::mat4 m_View = glm::mat4(1.0f);
    glm::mat4 m_InverseView = glm::mat4(1.0f);

    glm::vec3 m_Position;
    glm::vec3 m_ForwardDirection;

    float m_VerticalFOV, m_NearClip, m_FarClip;
    uint32_t m_ViewportWidth, m_ViewportHeight;

    glm::vec2 m_LastMousePosition = glm::vec2(0.0f);

    std::vector<glm::vec3> m_RayDirections;
};

#endif // CAMERA_H

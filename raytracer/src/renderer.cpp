#include "renderer.h"

#include "glm/common.hpp"
#include "glm/exponential.hpp"
#include "glm/geometric.hpp"
#include "scene.h"
#include <cfloat>
#include <limits>

namespace Utils
{
    static uint32_t ConvertToRGBA(const glm::vec4& color)
    {
        uint8_t r = (uint8_t)(color.r * 255.0f);
        uint8_t g = (uint8_t)(color.g * 255.0f);
        uint8_t b = (uint8_t)(color.b * 255.0f);
        uint8_t a = (uint8_t)(color.a * 255.0f);

        uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
        return result;
    }
}

Renderer::Renderer()
{
    m_RandomEngine.seed(std::random_device()());
}

void Renderer::OnResize(uint32_t width, uint32_t height)
{
    if (m_FinalImage)
    {
        if (width == m_FinalImage->GetWidth() &&
            height == m_FinalImage->GetHeight())
            return;
        // TODO: Implement Texture2D Resize functionality
        m_FinalImage = Elysium::Texture2D::Create(width, height);
    }
    else
    {
        m_FinalImage = Elysium::Texture2D::Create(width, height);
    }

    delete[] m_ImageData;
    m_ImageData = new uint32_t[width * height];
}

void Renderer::Render(const Scene& scene,
                      const Camera& camera)
{

    m_ActiveScene = &scene;
    m_ActiveCamera = &camera;

    for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
    {
        for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
        {
            glm::vec4 color = PerPixel(x, y);
            color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
            m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(color);
        }
    }

    m_FinalImage->SetData(m_ImageData, (m_FinalImage->GetWidth() * m_FinalImage->GetHeight()) * sizeof(uint32_t));
}

glm::vec4 Renderer::PerPixel(uint32_t x, uint32_t y)
{
    Ray ray;
    ray.Origin = m_ActiveCamera->GetPosition();
    ray.Direction = m_ActiveCamera->GetRayDirections()[x + y * m_FinalImage->GetWidth()];

    glm::vec3 finalColor;
    int bounces = 2;
    float multiplier = 1.0f;

    HitPayload payload = TraceRay(ray);

    for (size_t i = 0; i < bounces; i++)
    {
        if (payload.HitDistance < 0.0)
        {
            finalColor += glm::vec3(0.0f, 0.0f, 0.0f) * multiplier;
            break;
        }

        const Sphere& sphere = m_ActiveScene->Spheres[payload.ObjectIndex];

        glm::vec3 lightDir = glm::normalize(glm::vec3(-1, -1, -1));
        float d = glm::max(glm::dot(payload.WorldNormal, -lightDir), 0.0f);

        glm::vec3 sphereColor = sphere.Albido;
        sphereColor *= d;

        finalColor += sphereColor * multiplier;
        multiplier *= 0.7f;

        ray.Origin = payload.WorldPosition + payload.WorldNormal * 0.0001f;
        ray.Direction = glm::reflect(ray.Direction, payload.WorldNormal);
        payload = TraceRay(ray);
    }

    return glm::vec4(finalColor, 1.0f);
}

Renderer::HitPayload Renderer::TraceRay(const Ray& ray)
{
    // float radius = 0.5f;

    // (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2)
    // where
    // a = ray origin
    // b = ray direction
    // r = radius
    // t = hit distance

    int closestSphere = -1;
    float hitDistance = std::numeric_limits<float>::max();
    for (size_t i = 0; i < m_ActiveScene->Spheres.size(); i++)
    {
        const Sphere& sphere = m_ActiveScene->Spheres[i];
        glm::vec3 origin = ray.Origin - sphere.Position;

        float a = glm::dot(ray.Direction, ray.Direction);
        float b = 2.0f * glm::dot(origin, ray.Direction);
        float c = glm::dot(origin, origin) - sphere.Radius * sphere.Radius;

        // Quadratic formula discriminant:
        // b^2 - 4ac

        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0.0f)
            continue;

        // -b +- sqrt(discriminant) / 2a
        // float t1 = (-b + glm::sqrt(discriminant)) / (2.0f * a);
        float closestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);
        if (closestT > 0.0f && closestT < hitDistance)
        {
            hitDistance = closestT;
            closestSphere = (int)i;
        }
    }

    if (closestSphere < 0)
        return Miss(ray);

    return ClosestHit(ray, hitDistance, closestSphere);
}

Renderer::HitPayload Renderer::ClosestHit(const Ray &ray, float hitDistance, int objectIndex)
{
    HitPayload payload;
    payload.HitDistance = hitDistance;
    payload.ObjectIndex = objectIndex;

    const Sphere& sphere = m_ActiveScene->Spheres[objectIndex];

    glm::vec3 origin = ray.Origin - sphere.Position;
    payload.WorldPosition = origin + ray.Direction * hitDistance;
    payload.WorldNormal = glm::normalize(payload.WorldPosition);

    payload.WorldPosition += sphere.Position;

    return payload;
}

Renderer::HitPayload Renderer::Miss(const Ray &ray)
{
    HitPayload payload;
    payload.HitDistance = -1.0f;
    return payload;
}

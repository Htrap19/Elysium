#include "renderer.h"

#include "glm/geometric.hpp"

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

void Renderer::Render()
{
    for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
    {
        for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
        {
            glm::vec2 coord = { (float)x / (float)m_FinalImage->GetWidth(),
                                (float)y / (float)m_FinalImage->GetHeight() };
            coord = coord * 2.0f - 1.0f; // -1 -> 1
            m_ImageData[x + y * m_FinalImage->GetWidth()] = PerPixel(coord);
        }
    }

    m_FinalImage->SetData(m_ImageData, (m_FinalImage->GetWidth() * m_FinalImage->GetHeight()) * sizeof(uint32_t));
}

uint32_t Renderer::PerPixel(glm::vec2 coord)
{
    glm::vec3 rayDirection(coord.x, coord.y, -1.0f);

    glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
    float radius = 0.5f;

    // (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2)
    // where
    // a = ray origin
    // b = ray direction
    // r = radius
    // t = hit distance

    float a = glm::dot(rayDirection, rayDirection);
    float b = 2.0f * glm::dot(rayOrigin, rayDirection);
    float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

    // Quadratic formula discriminant:
    // b^2 - 4ac

    float discriminant = b * b - 4 * a * c;

    if (discriminant >= 0.0f)
        return 0xffff00ff;

    return 0xff000000;
}

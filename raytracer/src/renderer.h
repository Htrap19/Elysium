#ifndef RENDERER_H
#define RENDERER_H

#include "engine.h"

#include <random>

class Renderer
{
public:
    Renderer();

    void OnResize(uint32_t width, uint32_t height);
    void Render();

    Elysium::Shared<Elysium::Texture2D> GetFinalImage() const
    { return m_FinalImage; }

private:
    glm::vec4 PerPixel(glm::vec2 coord);

private:
    Elysium::Shared<Elysium::Texture2D> m_FinalImage;
    uint32_t* m_ImageData = nullptr;

    std::mt19937 m_RandomEngine;
    std::uniform_int_distribution<std::mt19937::result_type> m_Distribution;
};

#endif // RENDERER_H

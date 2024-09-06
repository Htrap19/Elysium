#ifndef RENDERER_H
#define RENDERER_H

#include "engine.h"

#include "camera.h"
#include "ray.h"
#include "scene.h"

#include <random>

class Renderer
{
public:
    struct Settings
    {
        bool Accumulate = true;
    };

public:
    Renderer();

    void OnResize(uint32_t width, uint32_t height);
    void Render(const Scene& scene, const Camera& camera);

    Elysium::Shared<Elysium::Texture2D> GetFinalImage() const
    { return m_FinalImage; }

    inline
    void ResetFrameIndex()
    { m_FrameIndex = 1; }

    inline
    Settings& GetSettings()
    { return m_Settings; }

private:
    struct HitPayload
    {
        float HitDistance;
        glm::vec3 WorldPosition;
        glm::vec3 WorldNormal;

        int ObjectIndex;
    };

    glm::vec4 PerPixel(uint32_t x, uint32_t y);

    HitPayload TraceRay(const Ray& ray);
    HitPayload ClosestHit(const Ray& ray, float hitDistance, int objectIndex);
    HitPayload Miss(const Ray& ray);

    float RandomFloat();
    glm::vec3 RandomVec3(float min, float max);

private:
    Elysium::Shared<Elysium::Texture2D> m_FinalImage;
    uint32_t* m_ImageData = nullptr;
    glm::vec4* m_AccumulationData = nullptr;
    uint32_t m_FrameIndex = 1;

    Settings m_Settings;

    const Scene* m_ActiveScene = nullptr;
    const Camera* m_ActiveCamera = nullptr;

    std::mt19937 m_RandomEngine;
    std::uniform_int_distribution<std::mt19937::result_type> m_Distribution;
};

#endif // RENDERER_H

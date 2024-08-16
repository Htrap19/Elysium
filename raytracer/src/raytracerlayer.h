#ifndef RAYTRACERLAYER_H
#define RAYTRACERLAYER_H

#include "engine.h"
#include <random>

using namespace Elysium;

class RayTracerLayer : public Layer
{
public:
    RayTracerLayer();

    virtual void OnAttach() override;
    virtual void OnUpdate(Elysium::Timestep timeStep) override;
    virtual void OnEvent(Elysium::Event &e) override;
    virtual void OnImGuiRender() override;
    virtual void OnDetach() override;

    void Render();

protected:
    void ShowDockspace(bool* pOpen);

private:
    bool m_ShowDockspace = true;
    Shared<Texture2D> m_Image;
    uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
    uint32_t* m_ImageData = nullptr;

    std::mt19937 m_RandomEngine;
    std::uniform_int_distribution<std::mt19937::result_type> m_Distribution;
};

#endif // RAYTRACERLAYER_H

#ifndef RAYTRACERLAYER_H
#define RAYTRACERLAYER_H

#include "engine.h"

#include "renderer.h"
#include "camera.h"

class RayTracerLayer : public Elysium::Layer
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
    Renderer m_Renderer;
    Camera m_Camera;
    float m_LastRenderTime = 0.0f;
    uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
};

#endif // RAYTRACERLAYER_H

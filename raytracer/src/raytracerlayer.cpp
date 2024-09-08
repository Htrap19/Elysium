#include "raytracerlayer.h"

#include "glm/gtc/type_ptr.hpp"
#include "platform/opengl/opengltexture.h"

#include <imgui.h>

#include "scene.h"
#include "timer.h"

RayTracerLayer::RayTracerLayer()
    : m_Camera(45.0f, 0.1f, 100.0f)
{
    Material& pinkSphere = m_Scene.Materials.emplace_back();
    pinkSphere.Albido = {1.0f, 0.0f, 1.0f};
    pinkSphere.Roughness = 0.0f;

    Material& blueSphere = m_Scene.Materials.emplace_back();
    blueSphere.Albido = {0.3f, 0.2f, 0.8f};
    blueSphere.Roughness = 0.1f;

    Material& orangeSphere = m_Scene.Materials.emplace_back();
    orangeSphere.Albido = { 0.8f, 0.5f, 0.2f };
    orangeSphere.Roughness = 0.1f;
    orangeSphere.EmissionColor = orangeSphere.Albido;
    orangeSphere.EmissionPower = 2.0f;

    {
        Sphere sphere;
        sphere.Position = {0.0f, 0.0f, 0.0f};
        sphere.Radius = 0.5f;
        sphere.MaterialIndex = 0;
        m_Scene.Spheres.push_back(sphere);
    }

    {
        Sphere sphere;
        sphere.Position = {0.0f, -101.0f, 0.0f};
        sphere.Radius = 100.0f;
        sphere.MaterialIndex = 1;
        m_Scene.Spheres.push_back(sphere);
    }

    {
        Sphere sphere;
        sphere.Position = { 2.0f, 0.0f, 0.0f };
        sphere.Radius = 1.0f;
        sphere.MaterialIndex = 2;
        m_Scene.Spheres.push_back(sphere);
    }
}

void RayTracerLayer::OnAttach()
{
}

void RayTracerLayer::OnUpdate(Elysium::Timestep timeStep)
{
    if (m_Camera.OnUpdate(timeStep))
        m_Renderer.ResetFrameIndex();
}

void RayTracerLayer::OnEvent(Elysium::Event &e)
{

}

void RayTracerLayer::OnImGuiRender()
{
    ShowDockspace(&m_ShowDockspace);

    ImGui::Begin("Settings");
    ImGui::Text("Last render: %.3fms", m_LastRenderTime);
    if (ImGui::Button("Render"))
    {
        Render();
    }
    ImGui::Checkbox("Accumulate", &m_Renderer.GetSettings().Accumulate);
    if (ImGui::Button("Reset"))
    {
        m_Renderer.ResetFrameIndex();
    }
    ImGui::End();

    ImGui::Begin("Scene");
    for (size_t i = 0; i < m_Scene.Spheres.size(); i++)
    {
        ImGui::PushID(i);

        auto& sphere = m_Scene.Spheres[i];
        ImGui::DragFloat3("Position", glm::value_ptr(sphere.Position), 0.1f);
        ImGui::DragFloat("Radius", &sphere.Radius, 0.1f);
        ImGui::DragInt("Material", &sphere.MaterialIndex, 1, 0, (int)m_Scene.Materials.size() - 1);

        ImGui::Separator();

        ImGui::PopID();
    }
    ImGui::End();

    ImGui::Begin("Materials");
    for (size_t i = 0; i < m_Scene.Materials.size(); i++)
    {
        ImGui::PushID(i);

        auto& material = m_Scene.Materials[i];
        ImGui::ColorEdit3("Albido", glm::value_ptr(material.Albido));
        ImGui::DragFloat("Roughness", &material.Roughness, 0.05f, 0.0f, 1.0f);
        ImGui::DragFloat("Metallic", &material.Metallic, 0.05f, 0.0f, 1.0f);
        ImGui::ColorEdit3("Emission Color", glm::value_ptr(material.EmissionColor));
        ImGui::DragFloat("Emisison Power", &material.EmissionPower, 0.05f, 0.0f, FLT_MAX);

        ImGui::Separator();

        ImGui::PopID();
    }
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Viewport");

    m_ViewportWidth = ImGui::GetContentRegionAvail().x;
    m_ViewportHeight = ImGui::GetContentRegionAvail().y;

    auto image = m_Renderer.GetFinalImage();
    if (image)
    {
        auto openGLImage = static_cast<Elysium::OpenGLTexture2D*>(image.get());
        ImGui::Image((void*)(intptr_t)openGLImage->GetID(),
                     { (float)image->GetWidth(),
                       (float)image->GetHeight() },
                     ImVec2(0.0f, 1.0f),
                     ImVec2(1.0f, 0.0f));
    }

    ImGui::End();
    ImGui::PopStyleVar();
    Render();
}

void RayTracerLayer::OnDetach()
{

}

void RayTracerLayer::Render()
{
    Timer timer;

    m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
    m_Camera.OnResize(m_ViewportWidth, m_ViewportHeight);
    m_Renderer.Render(m_Scene, m_Camera);

    m_LastRenderTime = timer.EllapsedMillis();
}

void RayTracerLayer::ShowDockspace(bool *pOpen)
{
    static bool optFullScreen = true;
    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None; // Config flags for the Dockspace

    ImGuiWindowFlags mainWindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    if (optFullScreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        mainWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        mainWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
        mainWindowFlags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", pOpen, mainWindowFlags);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);
    }
    else
    {
        // Docking is DISABLED - Show a warning message
        ES_WARN("Docking is DISABLED!");
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

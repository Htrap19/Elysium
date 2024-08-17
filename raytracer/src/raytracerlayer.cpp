#include "raytracerlayer.h"

#include "platform/opengl/opengltexture.h"

#include <imgui.h>

#include "timer.h"

RayTracerLayer::RayTracerLayer()
    : m_Camera(45.0f, 0.1f, 100.0f)
{}

void RayTracerLayer::OnAttach()
{
}

void RayTracerLayer::OnUpdate(Elysium::Timestep timeStep)
{
    m_Camera.OnUpdate(timeStep);
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
    m_Renderer.Render(m_Camera);

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

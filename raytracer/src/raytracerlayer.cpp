#include "raytracerlayer.h"
#include "core/utility.h"
#include "imgui.h"
#include "platform/opengl/opengltexture.h"

#include <random>

RayTracerLayer::RayTracerLayer() {}

void RayTracerLayer::OnAttach()
{
    m_RandomEngine.seed(std::random_device()());
}

void RayTracerLayer::OnUpdate(Elysium::Timestep timeStep)
{

}

void RayTracerLayer::OnEvent(Elysium::Event &e)
{

}

void RayTracerLayer::OnImGuiRender()
{
    ShowDockspace(&m_ShowDockspace);

    ImGui::Begin("Settings");
    if (ImGui::Button("Render"))
    {
        Render();
    }
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Viewport");

    m_ViewportWidth = ImGui::GetContentRegionAvail().x;
    m_ViewportHeight = ImGui::GetContentRegionAvail().y;

    if (m_Image)
    {
        auto openGLImage = static_cast<OpenGLTexture2D*>(m_Image.get());
        ImGui::Image((void*)(intptr_t)openGLImage->GetID(),
                     { (float)m_Image->GetWidth(),
                       (float)m_Image->GetHeight() });
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
    if (!m_Image ||
        m_ViewportWidth != m_Image->GetWidth() ||
        m_ViewportHeight != m_Image->GetHeight())
    {
        m_Image = Texture2D::Create(m_ViewportWidth, m_ViewportHeight);
        delete[] m_ImageData;
        m_ImageData = new uint32_t[m_ViewportWidth * m_ViewportHeight];
    }

    for (uint32_t i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
    {
        m_ImageData[i] = m_Distribution(m_RandomEngine);
        m_ImageData[i] |= 0xff000000;
    }

    m_Image->SetData(m_ImageData, (m_ViewportWidth * m_ViewportHeight) * sizeof(uint32_t));
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
}

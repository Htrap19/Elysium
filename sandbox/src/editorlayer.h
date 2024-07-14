#pragma once

#include "scenelayer.h"

class EditorLayer : public SceneLayer
{
public:
	EditorLayer()
	{
		m_Panel.SetContext(m_Scene);
	}

	virtual void OnEvent(Elysium::Event& e) override
	{
		Elysium::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Elysium::WindowResizeEvent>(ES_BIND_EVENT_FN(EditorLayer::OnResize));
	}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		if (m_FrameBuffer && !m_Running)
			m_FrameBuffer->Bind();

		if (m_Running && m_ResizeScene)
		{
			auto& window = Elysium::Application::GetInstance().GetWindow();
			m_Scene->Resize(window.GetWidth(), window.GetHeight());
			m_ResizeScene = false;
		}

		SceneLayer::OnUpdate(ts);

		if (m_FrameBuffer && !m_Running)
			m_FrameBuffer->Unbind();
	}

	virtual void OnImGuiRender() override
	{
		if (m_Running)
			return;

		ShowDockspace(&m_ShowDockspace);

		m_Panel.OnImGuiRender();

		ImGui::Begin("Renderer Stats");
		auto stats = Elysium::Renderer::GetStats();
		ImGui::Text("Draw calls: %d", stats.DrawCalls);
		ImGui::Text("Total vertices: %d", stats.TotalVertices);
		ImGui::Text("Total indices: %d", stats.TotalIndices);
		ImGui::Text("Total entities: %d", stats.ModelCount);
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,
							ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		auto width = ImGui::GetWindowWidth();
		auto height = ImGui::GetWindowHeight() - 20;

		if (!m_FrameBuffer)
		{
			m_FrameBuffer = Elysium::FrameBuffer::Create((uint32_t)width,
														 (uint32_t)height);
			m_Scene->Resize((uint32_t)width,
							(uint32_t)height);
		}

		if (m_FrameBuffer->GetWidth() != width ||
			m_FrameBuffer->GetHeight() != height)
		{
			m_FrameBuffer->Resize((uint32_t)width,
								  (uint32_t)height);
			m_Scene->Resize((uint32_t)width,
							(uint32_t)height);
		}

		auto textureId = m_FrameBuffer->GetColorAttachmentId();
		ImGui::Image((void*)(intptr_t)textureId,
					 ImVec2(m_FrameBuffer->GetWidth(), m_FrameBuffer->GetHeight()),
					 ImVec2{ 0, 1 }, 
					 ImVec2{ 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();
	}

protected:
	void ShowDockspace(bool* pOpen)
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

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Scene"))
			{
				ImGui::MenuItem("Run", nullptr, &m_Running);

				if (ImGui::BeginMenu("Options"))
				{
					ImGui::MenuItem("Show axis", nullptr, &m_ShowAxis);

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Options"))
			{
				ImGui::MenuItem("Fullscreen", nullptr, &optFullScreen);
				ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspaceFlags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_NoSplit; }
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspaceFlags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_NoResize; }
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspaceFlags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspaceFlags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, optFullScreen)) { dockspaceFlags ^= ImGuiDockNodeFlags_PassthruCentralNode; }

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

	bool OnResize(Elysium::WindowResizeEvent& e)
	{
		if (m_Running)
			m_Scene->Resize(e.GetWidth(), e.GetHeight());

		return false;
	}

protected:
	Elysium::Shared<Elysium::FrameBuffer> m_FrameBuffer;

	SceneHierarchicalPanel m_Panel;

	bool m_ShowDockspace = true;
	bool m_Running = false;
	bool m_ResizeScene = true;
};
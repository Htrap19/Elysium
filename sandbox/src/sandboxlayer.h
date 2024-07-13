#pragma once

#include "scenelayer.h"
#include "wasdcontroller.h"

#include "ellipticalmotion.h"
#include "cameraellipticalmotion.h"

#include "engine.h"

#include <imgui.h>
#include <glm/glm.hpp>

class SandboxLayer : public SceneLayer
{
public:
	virtual void OnAttach() override
	{
		ES_INFO("Sandbox layer attached!");

		m_Sun = m_Scene->CreateEntity("Sun");
		m_Sun.AddComponent<Elysium::MeshComponent>("resources/models/sun/scene.gltf");
		auto& tc = m_Sun.GetComponent<Elysium::TransformComponent>();
		tc.Scale = glm::vec3(1.0f);
		tc.Position = glm::vec3(5.0f, 0.0f, 0.0f);

		m_Earth = m_Scene->CreateEntity("Earth");
		m_Earth.AddComponent<Elysium::MeshComponent>("resources/models/earth/scene.gltf");
		auto& tce = m_Earth.GetComponent<Elysium::TransformComponent>();
		tce.Position = glm::vec3(-10.0f, 0.0f, -10.0f);

		m_Mercury = m_Scene->CreateEntity("Mercury");
		m_Mercury.AddComponent<Elysium::MeshComponent>("resources/models/mercury_sharp/scene.gltf");
		auto& tcm = m_Mercury.GetComponent<Elysium::TransformComponent>();
		tcm.Position = glm::vec3(-20.0f, 0.0f, -20.0f);

		m_Mercury.AddComponent<Elysium::NativeScriptComponent>()
			.Bind<EllipticalMotion>();

		auto spaceSkyBox = Elysium::CubeMap::Create(
		{
			"resources/textures/skybox/right.png",
			"resources/textures/skybox/left.png",
			"resources/textures/skybox/top.png",
			"resources/textures/skybox/bottom.png",
			"resources/textures/skybox/front.png",
			"resources/textures/skybox/back.png",
		});
		m_Scene->SetSkyBox(spaceSkyBox);

		m_Camera = m_Scene->CreateEntity("Camera");
		auto& cc = m_Camera.AddComponent<Elysium::CameraComponent>(glm::vec3(0.0f, 0.0f, 3.0f));
		cc.Camera.SetAspectRatio(m_Scene->GetAspectRatio());
		m_Camera.AddComponent<Elysium::NativeScriptComponent>()
			.Bind<WASDController>();

		m_AxisLength = cc.Camera.GetFarPlane();
	}

	virtual void OnEvent(Elysium::Event& e) override
	{
		Elysium::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Elysium::WindowResizeEvent>(ES_BIND_EVENT_FN(SandboxLayer::OnResize));
	}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		Elysium::RenderCommand::SetClearColor(m_BackgroundColor);

		if (m_Running)
		{
			if (m_ResizeScene)
			{
				auto& window = Elysium::Application::GetInstance().GetWindow();
				m_Scene->Resize(window.GetWidth(), window.GetHeight());
				m_ResizeScene = false;
			};
			m_Scene->OnUpdate(ts);
		}

		SceneLayer::OnUpdate(ts);

		auto& cc = m_Camera.GetComponent<Elysium::CameraComponent>();

		if (Elysium::Input::IsKeyPressed(Elysium::Key::Escape))
		{
			m_Running = false;
			m_ResizeScene = true;
		}

		auto wasdnsc = m_Camera
			.GetComponent<Elysium::NativeScriptComponent>()
			.As<WASDController>();

		wasdnsc->SetEnabled(m_Running);
	}

	virtual void OnImGuiRender() override
	{
		if (m_Running)
			return;

		ShowDockspace(&m_ShowDockspace);

		SceneLayer::OnImGuiRender();
	}

private:
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

		ImGui::Begin("DockSpace", pOpen, mainWindowFlags);

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
				ImGui::Separator();

				if (ImGui::MenuItem("Close", nullptr, false, pOpen != nullptr))
					if (pOpen != nullptr)
						*pOpen = false;
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Settings"))
			{
				ImGui::MenuItem("Show axis", nullptr, &m_ShowAxis);

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

	bool OnResize(Elysium::WindowResizeEvent& e)
	{
		if (m_Running)
		{
			m_Scene->Resize(e.GetWidth(), e.GetHeight());
		}
		return false;
	}

private:
	glm::vec4 m_BackgroundColor = { 0.3f, 0.3f, 0.5f, 1.0f };

	Elysium::Entity m_Sun;

	Elysium::Entity m_Earth;
	Elysium::Entity m_Mercury;

	Elysium::Entity m_Camera;

	bool m_Running = false;
	bool m_ResizeScene = true;
	bool m_ShowDockspace = true;
	float m_LastX = 0.0f, m_LastY = 0.0f;
	float m_DeltaX = 0.0f, m_DeltaY = 0.0f;
};

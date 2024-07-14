#pragma once

#include "editorlayer.h"
#include "wasdcontroller.h"

#include "engine.h"

#include <imgui.h>
#include <glm/glm.hpp>

class SandboxLayer : public EditorLayer
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
	}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		Elysium::RenderCommand::SetClearColor(m_BackgroundColor);
		
		EditorLayer::OnUpdate(ts);

		if (Elysium::Input::IsKeyPressed(Elysium::Key::Escape))
			m_Running = false;

		auto nsc = m_Camera.GetComponent<Elysium::NativeScriptComponent>().Instance;
		auto wasdnsc = static_cast<WASDController*>(nsc);

		wasdnsc->SetEnabled(m_Running);
	}

private:
	glm::vec4 m_BackgroundColor = { 0.3f, 0.3f, 0.5f, 1.0f };

	Elysium::Entity m_Sun;
	Elysium::Entity m_Earth;

	Elysium::Entity m_Camera;
};

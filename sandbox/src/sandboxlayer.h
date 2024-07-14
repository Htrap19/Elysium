#pragma once

#include "editorlayer.h"
#include "wasdcontroller.h"

#include "ellipticalmotion.h"
#include "cameraellipticalmotion.h"

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

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		Elysium::RenderCommand::SetClearColor(m_BackgroundColor);
		
		EditorLayer::OnUpdate(ts);

		if (Elysium::Input::IsKeyPressed(Elysium::Key::Escape))
		{
			m_Running = false;
			m_ResizeScene = true;
		}

		auto wasdnsc = m_Camera
			.GetComponent<Elysium::NativeScriptComponent>()
			.As<WASDController>();

		wasdnsc->SetEnabled(m_Running);

		auto emnsc = m_Mercury
			.GetComponent<Elysium::NativeScriptComponent>()
			.As<EllipticalMotion>();
		emnsc->SetPlaying(m_Running);
	}

	virtual void OnImGuiRender() override
	{
		EditorLayer::OnImGuiRender();

		ImGui::Begin("Motion settings");
		auto emnsc = m_Mercury
			.GetComponent<Elysium::NativeScriptComponent>()
			.As<EllipticalMotion>();

		auto centerPoint = emnsc->GetCenter();
		ImGui::DragFloat3("Center", &centerPoint.x);
		emnsc->SetCenter(centerPoint);

		auto movementSpeed = emnsc->GetMovementSpeed();
		ImGui::DragFloat("Movement speed", &movementSpeed);
		emnsc->SetMovementSpeed(movementSpeed);

		auto theta = emnsc->GetTheta();
		ImGui::DragFloat("Theta", &theta);
		emnsc->SetTheta(theta);

		auto phi = emnsc->GetPhi();
		ImGui::DragFloat("Phi", &phi);
		emnsc->SetPhi(phi);

		auto a = emnsc->GetA();
		ImGui::DragFloat("A", &a);
		emnsc->SetA(a);

		auto b = emnsc->GetB();
		ImGui::DragFloat("B", &b);
		emnsc->SetB(b);

		auto c = emnsc->GetC();
		ImGui::DragFloat("C", &c);
		emnsc->SetC(c);

		ImGui::End();
	}

private:
	glm::vec4 m_BackgroundColor = { 0.3f, 0.3f, 0.5f, 1.0f };

	Elysium::Entity m_Sun;

	Elysium::Entity m_Earth;
	Elysium::Entity m_Mercury;

	Elysium::Entity m_Camera;
};

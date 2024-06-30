#pragma once

#include "scenelayer.h"

#include "engine.h"

#include <imgui.h>
#include <glm/glm.hpp>

class SandboxLayer : public SceneLayer
{
public:
	virtual void OnAttach() override
	{
		ES_INFO("Sandbox layer attached!");

		m_Sun = m_Scene->CreateEntity();
		m_Sun.AddComponent<Elysium::MeshComponent>("resources/models/sun/scene.gltf");
		auto& tc = m_Sun.GetComponent<Elysium::TransformComponent>();
		tc.Scale = glm::vec3(1.0f);
		tc.Position = glm::vec3(5.0f, 0.0f, 0.0f);

		m_Earth = m_Scene->CreateEntity();
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

		m_Camera = m_Scene->CreateEntity();
		auto& cc = m_Camera.AddComponent<Elysium::CameraComponent>(glm::vec3(0.0f, 0.0f, 3.0f));
	}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		Elysium::RenderCommand::SetClearColor(m_BackgroundColor);
		SceneLayer::OnUpdate(ts);

		if (!m_Running)
			return;

		auto& cc = m_Camera.GetComponent<Elysium::CameraComponent>();

		if (Elysium::Input::IsKeyPressed(Elysium::Key::W))
			cc.Camera.MoveForward(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::S))
			cc.Camera.MoveBackward(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::A))
			cc.Camera.MoveLeft(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::D))
			cc.Camera.MoveRight(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::Space))
			cc.Camera.MoveUp(ts);
		if (Elysium::Input::IsKeyPressed(Elysium::Key::LeftShift))
			cc.Camera.MoveDown(ts);

		auto cursor = Elysium::Input::GetCursorPosition();
		m_DeltaX = cursor.x - m_LastX;
		m_DeltaY = m_LastY - cursor.y;

		m_LastX = cursor.x;
		m_LastY = cursor.y;

		cc.Camera.MoveCursor(m_DeltaX, m_DeltaY);

		if (Elysium::Input::IsKeyPressed(Elysium::Key::Escape))
			m_Running = false;
	}

	virtual void OnImGuiRender() override
	{
		if (m_Running)
			return;

		SceneLayer::OnImGuiRender();

		ImGui::Begin("Window");

		ImGui::ColorEdit4("Pick background", &m_BackgroundColor[0]);

		if (ImGui::CollapsingHeader("Sun"))
		{
			auto& tc = m_Sun.GetComponent<Elysium::TransformComponent>();
			ImGui::DragFloat3("Position", &tc.Position[0], .1f);
			ImGui::DragFloat3("Rotation", &tc.Rotate[0], .1f);
			ImGui::DragFloat3("Scale", &tc.Scale[0], .1f);

			if (ImGui::Button("View"))
			{
				auto& cc = m_Camera.GetComponent<Elysium::CameraComponent>();
				cc.Camera.SetFront(tc.Position);
				cc.Camera.SetPosition(tc.Position - (tc.Scale * 30.0f));
				cc.Camera.SetYaw(0.0f);
				cc.Camera.SetPitch(0.0f);
			}
		}

		if (ImGui::CollapsingHeader("Earth"))
		{
			auto& earthTransformComponent = m_Earth.GetComponent<Elysium::TransformComponent>();
			ImGui::DragFloat3("Position", &earthTransformComponent.Position[0], .1f);
			ImGui::DragFloat3("Rotation", &earthTransformComponent.Rotate[0], .1f);
			ImGui::DragFloat3("Scale", &earthTransformComponent.Scale[0], .1f);

			if (ImGui::Button("View"))
			{
				auto& cc = m_Camera.GetComponent<Elysium::CameraComponent>();
				cc.Camera.SetFront(earthTransformComponent.Position);
			}
		}

		if (ImGui::CollapsingHeader("Camera"))
		{
			auto& cc = m_Camera.GetComponent<Elysium::CameraComponent>();
			auto turningSpeed = cc.Camera.GetTurningSpeed();
			ImGui::DragFloat("Turning speed", &turningSpeed);
			cc.Camera.SetTurningSpeed(turningSpeed);

			auto movementSpeed = cc.Camera.GetMovementSpeed();
			ImGui::DragFloat("Novement speed", &movementSpeed);
			cc.Camera.SetMovementSpeed(movementSpeed);
		}

		if (ImGui::Button("Run"))
		{
			m_Running = true;
		}

		ImGui::End();
	}

private:
	glm::vec4 m_BackgroundColor = { 0.3f, 0.3f, 0.5f, 1.0f };

	Elysium::Entity m_Sun;
	Elysium::Entity m_Earth;

	Elysium::Entity m_Camera;

	bool m_Running = false;
	float m_LastX = 0.0f, m_LastY = 0.0f;
	float m_DeltaX = 0.0f, m_DeltaY = 0.0f;
};

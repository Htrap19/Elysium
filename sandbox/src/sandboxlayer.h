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
		tc.Scale = glm::vec3(0.1f);
		tc.Position = glm::vec3(5.0f, 0.0f, -20.0f);

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
	}

	virtual void OnUpdate() override
	{
		Elysium::RenderCommand::SetClearColor(m_BackgroundColor);
		SceneLayer::OnUpdate();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Window");

		ImGui::ColorEdit4("Pick background", &m_BackgroundColor[0]);

		if (ImGui::CollapsingHeader("Sun"))
		{
			auto& tc = m_Sun.GetComponent<Elysium::TransformComponent>();
			ImGui::DragFloat3("Position", &tc.Position[0], .1f);
			ImGui::DragFloat3("Rotation", &tc.Rotate[0], .1f);
			ImGui::DragFloat3("Scale", &tc.Scale[0], .1f);
		}

		if (ImGui::CollapsingHeader("Earth"))
		{
			auto& earthTransformComponent = m_Earth.GetComponent<Elysium::TransformComponent>();
			ImGui::DragFloat3("Position", &earthTransformComponent.Position[0], .1f);
			ImGui::DragFloat3("Rotation", &earthTransformComponent.Rotate[0], .1f);
			ImGui::DragFloat3("Scale", &earthTransformComponent.Scale[0], .1f);
		}

		ImGui::End();

		SceneLayer::OnImGuiRender();
	}

private:
	glm::vec4 m_BackgroundColor = { 0.3f, 0.3f, 0.5f, 1.0f };

	Elysium::Entity m_Sun;
	Elysium::Entity m_Earth;
};

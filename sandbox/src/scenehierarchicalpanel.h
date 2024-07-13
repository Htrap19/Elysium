#pragma once

#include "engine.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <entt/entt.hpp>

class SceneHierarchicalPanel
{
public:
	SceneHierarchicalPanel() = default;
	SceneHierarchicalPanel(const Elysium::Shared<Elysium::Scene>& scene)
		: m_Context(scene)
	{}

	inline void SetContext(const Elysium::Shared<Elysium::Scene>& scene)
	{ m_Context = scene; }

	virtual void OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry
			.view<Elysium::TagComponent>()
			.each([this](auto entity, Elysium::TagComponent& tc)
			{
				auto ent = Elysium::Entity(entity, m_Context.get());
				DrawEntity(ent);
			});

		ImGui::End();
	}

protected:
	void DrawEntity(Elysium::Entity& entity)
	{
		auto& tag = entity.GetComponent<Elysium::TagComponent>().Tag;
		if (ImGui::CollapsingHeader(tag.c_str(), true))
		{
			ImGui::InputText("Tag", &tag);

			auto& tc = entity.GetComponent<Elysium::TransformComponent>();

			ImGui::PushID(tag.c_str());
			ImGui::SeparatorText("Transform");
			ImGui::DragFloat3("Position", &tc.Position.x, 0.1f);
			ImGui::DragFloat3("Rotation", &tc.Rotate.x, 0.1f);
			ImGui::DragFloat3("Scale", &tc.Scale.x, 0.1f);

			if (entity.HasComponent<Elysium::CameraComponent>())
			{
				ImGui::SeparatorText("Camera");

				auto& cc = entity.GetComponent<Elysium::CameraComponent>();

				auto position = cc.Camera.GetPosition();
				ImGui::DragFloat3("Position", &position.x, .1f);
				cc.Camera.SetPosition(position);

				auto nearPlane = cc.Camera.GetNearPlane();
				ImGui::DragFloat("Near plane", &nearPlane);
				cc.Camera.SetNearPlane(nearPlane);

				auto farPlane = cc.Camera.GetFarPlane();
				ImGui::DragFloat("Far plane", &farPlane);
				cc.Camera.SetFarPlane(farPlane);

				auto fov = cc.Camera.GetFOV();
				ImGui::DragFloat("FOV", &fov);
				cc.Camera.SetFOV(fov);

				auto turningSpeed = cc.Camera.GetTurningSpeed();
				ImGui::DragFloat("Turning speed", &turningSpeed);
				cc.Camera.SetTurningSpeed(turningSpeed);

				auto movementSpeed = cc.Camera.GetMovementSpeed();
				ImGui::DragFloat("Novement speed", &movementSpeed);
				cc.Camera.SetMovementSpeed(movementSpeed);
			}

			ImGui::PopID();
		}
	}

private:
	Elysium::Shared<Elysium::Scene> m_Context;
};
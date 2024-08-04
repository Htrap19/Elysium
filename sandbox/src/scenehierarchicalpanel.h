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

        m_Context->GetRegistry()
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

		ImGui::PushID(tag.c_str());
		if (ImGui::CollapsingHeader(tag.c_str(), true))
		{
			ImGui::InputText("Tag", &tag);

			auto& tc = entity.GetComponent<Elysium::TransformComponent>();

			ImGui::SeparatorText("Transform");
			ImGui::DragFloat3("Position", &tc.Position.x, 0.1f);
			ImGui::DragFloat3("Rotation", &tc.Rotate.x, 0.1f);
			ImGui::DragFloat3("Scale", &tc.Scale.x, 0.1f);

			if (entity.HasComponent<Elysium::CameraComponent>())
			{
				ImGui::SeparatorText("Camera");

				auto& cc = entity.GetComponent<Elysium::CameraComponent>();

                auto position = cc.CameraIns.GetPosition();
				ImGui::DragFloat3("Position", &position.x, .1f);
                cc.CameraIns.SetPosition(position);

                auto nearPlane = cc.CameraIns.GetNearPlane();
				ImGui::DragFloat("Near plane", &nearPlane);
                cc.CameraIns.SetNearPlane(nearPlane);

                auto farPlane = cc.CameraIns.GetFarPlane();
				ImGui::DragFloat("Far plane", &farPlane);
                cc.CameraIns.SetFarPlane(farPlane);

                auto fov = cc.CameraIns.GetFOV();
				ImGui::DragFloat("FOV", &fov);
                cc.CameraIns.SetFOV(fov);

                auto turningSpeed = cc.CameraIns.GetTurningSpeed();
				ImGui::DragFloat("Turning speed", &turningSpeed);
                cc.CameraIns.SetTurningSpeed(turningSpeed);

                auto movementSpeed = cc.CameraIns.GetMovementSpeed();
				ImGui::DragFloat("Novement speed", &movementSpeed);
                cc.CameraIns.SetMovementSpeed(movementSpeed);
			}

			if (entity.HasComponent<Elysium::MeshComponent>())
			{
				auto& mc = entity.GetComponent<Elysium::MeshComponent>();
				ImGui::SeparatorText("Mesh");
				ImGui::InputText("Path", &mc.Path, ImGuiInputTextFlags_ReadOnly);
			}
		}

		ImGui::PopID();
	}

private:
	Elysium::Shared<Elysium::Scene> m_Context;
};

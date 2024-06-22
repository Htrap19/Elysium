#pragma once

#include "engine.h"

#include <imgui.h>

class SceneLayer : public Elysium::Layer
{
public:
	SceneLayer()
	{
		m_Scene = Elysium::MakeShared<Elysium::Scene>();
	}

	virtual void OnEvent(Elysium::Event& e) override
	{
		Elysium::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Elysium::WindowResizeEvent>(ES_BIND_EVENT_FN(SceneLayer::OnResize));
	}

	virtual void OnUpdate() override
	{
		m_Scene->OnUpdate();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Renderer Stats");
		auto stats = Elysium::Renderer::GetStats();
		ImGui::Text("Draw calls: %d", stats.DrawCalls);
		ImGui::Text("Total vertices: %d", stats.TotalVertices);
		ImGui::Text("Total indices: %d", stats.TotalIndices);
		ImGui::Text("Total entities: %d", stats.ModelCount);
		ImGui::End();
	}

protected:
	bool OnResize(Elysium::WindowResizeEvent& e)
	{
		m_Scene->Resize(e.GetWidth(), e.GetHeight());
		return false;
	}

protected:
	Elysium::Shared<Elysium::Scene> m_Scene;
};
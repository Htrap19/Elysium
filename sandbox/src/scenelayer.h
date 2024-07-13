#pragma once

#include "engine.h"

#include "scenehierarchicalpanel.h"

#include <imgui.h>

class SceneLayer : public Elysium::Layer
{
public:
	SceneLayer()
	{
		m_Scene = Elysium::MakeShared<Elysium::Scene>();
		m_Panel.SetContext(m_Scene);
	}

	virtual void OnEvent(Elysium::Event& e) override
	{
		Elysium::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Elysium::WindowResizeEvent>(ES_BIND_EVENT_FN(SceneLayer::OnResize));
	}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		if (m_FrameBuffer)
			m_FrameBuffer->Bind();

		Elysium::RenderCommand::Clear();
		m_Scene->OnUpdate(ts);

		if (m_FrameBuffer)
			m_FrameBuffer->Unbind();
	}

	virtual void OnImGuiRender() override
	{
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
			m_Scene->Resize(width, height);
		}

		auto textureId = m_FrameBuffer->GetColorAttachmentId();
		ImGui::Image((void*)(intptr_t)textureId, ImVec2(m_FrameBuffer->GetWidth(),
														m_FrameBuffer->GetHeight()));
	
		ImGui::End();
		ImGui::PopStyleVar();
	}

protected:
	bool OnResize(Elysium::WindowResizeEvent& e)
	{
		return false;
	}

protected:
	Elysium::Shared<Elysium::Scene> m_Scene;
	Elysium::Shared<Elysium::FrameBuffer> m_FrameBuffer;

	SceneHierarchicalPanel m_Panel;
};
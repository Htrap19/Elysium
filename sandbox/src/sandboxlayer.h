#pragma once

#include "engine.h"

#include <imgui.h>
#include <glm/glm.hpp>

class SandboxLayer : public Elysium::Layer
{
public:
	virtual void OnAttach() override
	{
		ES_INFO("Sandbox layer attached!");
		m_Shader = Elysium::Shader::Create("resources/shaders/renderer.glsl");
		m_VertexArray = Elysium::VertexArray::Create();
		m_Texture = Elysium::Texture2D::Create("resources/textures/brick.png");

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f,		0.5f, 1.0f
		};

		m_VertexBuffer = Elysium::VertexBuffer::Create(sizeof(vertices), vertices);
		m_VertexBuffer->SetLayout(Elysium::BufferLayout({
				Elysium::ShaderDataType::Float3, // layout location (0: a_Pos)
				Elysium::ShaderDataType::Float2, // layout location (0: a_TexCoord)
			}));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	}

	virtual void OnUpdate() override
	{
		Elysium::RenderCommand::SetClearColor(m_BackgroundColor);

		m_Shader->Bind();
		m_Shader->SetUniformVec4("u_Color", m_TriangleColor);
		m_Texture->Bind();
		Elysium::Renderer::Draw(m_VertexArray, m_Shader);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Window");

		ImGui::Text("Hello world!");
		ImGui::ColorEdit4("Pick background", &m_BackgroundColor[0]);
		ImGui::ColorEdit4("Triangle Color", &m_TriangleColor[0]);

		ImGui::End();
	}

private:
	glm::vec4 m_BackgroundColor = { 0.3f, 0.3f, 0.5f, 1.0f };
	glm::vec4 m_TriangleColor = { 0.3f, 0.2f, 0.5f, 1.0f };
	Elysium::Shared<Elysium::Shader> m_Shader;
	Elysium::Shared<Elysium::VertexArray> m_VertexArray;
	Elysium::Shared<Elysium::VertexBuffer> m_VertexBuffer;
	Elysium::Shared<Elysium::Texture2D> m_Texture;
};

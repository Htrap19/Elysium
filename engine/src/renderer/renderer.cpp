#include "renderer.h"

#include "renderer/buffer.h"
#include "renderer/texture.h"
#include "renderer/rendercommand.h"

#include "core/log.h"

#include "scene/components.h"

#include <glm/glm.hpp>

#include <array>
#include <unordered_map>

#define SHADER_FILE					"resources/shaders/renderer.glsl"

#define PROJECTION_UNIFORM_NAME		"u_Projection"
#define VIEW_UNIFORM_NAME			"u_View"
#define MODEL_UNIFORM_NAME			"u_Model"
#define TEXTURE_UNIFORM_NAME		"u_Texture"

namespace Elysium
{
	namespace Util
	{
		static constexpr size_t MaxTrianglesCount		= (4294967295) / 512; // == UINT_MAX / 512
		static constexpr size_t MaxVerticesCount		= MaxTrianglesCount * 3;
		static constexpr size_t MaxIndicesCount			= MaxTrianglesCount * 3;
		static constexpr size_t MaxTexturesCount		= 32;
		static constexpr size_t MaxModelMatricesCount	= 32;

		struct RendererData
		{
			Shared<VertexArray> VertexArray;
			Shared<VertexBuffer> VertexBuffer;
			Shared<IndexBuffer> IndexBuffer;

			Shared<Shader> Shader;

			std::array<Shared<Texture2D>, MaxTexturesCount> Textures;
			std::unordered_map<uint32_t, glm::mat4> ModelMatrices;

			size_t TextureSlotIndex = 1; // 0 - plain texture
			size_t IndexOffset		= 0;
			size_t IndexCount		= 0;
			size_t ModelsCount		= 0;
		};
	}

	static Util::RendererData s_Data;

	static void StartBatch()
	{
		s_Data.TextureSlotIndex = 1;
		s_Data.IndexOffset = 0;
		s_Data.IndexCount = 0;
		s_Data.ModelsCount = 0;
	}

	static void NextBatch()
	{
		Renderer::Flush();
		StartBatch();
	}

	void Renderer::Init()
	{
		s_Data.VertexArray = VertexArray::Create();
		s_Data.VertexBuffer = VertexBuffer::Create(Util::MaxVerticesCount * sizeof(Renderer::Vertex));
		s_Data.IndexBuffer = IndexBuffer::Create(Util::MaxIndicesCount);

		s_Data.VertexBuffer->SetLayout(BufferLayout({
				ShaderDataType::Float3, // (location = 0) vec3 a_Pos;
				ShaderDataType::Float2, // (location = 1) vec2 a_TexCoord;
				ShaderDataType::Int,	// (location = 2) int  a_TexIndex;
				ShaderDataType::Int,	// (location = 3) int  a_ModelIndex;
				ShaderDataType::Float4,	// (location = 3) vec4 a_Color;
			}));

		s_Data.VertexArray->AddVertexBuffer(s_Data.VertexBuffer);
		s_Data.VertexArray->SetIndexBuffer(s_Data.IndexBuffer);

		s_Data.Shader = Shader::Create(SHADER_FILE);

		auto plainTexture = Texture2D::Create(1, 1);
		uint32_t white = 0xffffffff;
		plainTexture->SetData(&white, sizeof(uint32_t));

		s_Data.Textures[0] = plainTexture;
	}

	void Renderer::Begin(const glm::mat4& projection,
						 const glm::mat4& view)
	{
		ResetStats();

		s_Data.Shader->Bind();
		s_Data.Shader->SetUniformMat4(PROJECTION_UNIFORM_NAME, projection);
		s_Data.Shader->SetUniformMat4(VIEW_UNIFORM_NAME, view);

		StartBatch();
	}

	void Renderer::End()
	{
		Flush();
	}

	void Renderer::Flush()
	{
		if (s_Data.IndexCount == 0)
			return; // Nothing to draw

		s_Data.Shader->Bind();

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			s_Data.Textures[i]->Bind(i);
			s_Data.Shader->SetUniformi(TEXTURE_UNIFORM_NAME + ("[" + std::to_string(i) + "]"), i);
		}

		for (uint32_t i = 0; i < s_Data.ModelsCount; i++)
		{
			s_Data.Shader->SetUniformMat4(MODEL_UNIFORM_NAME + ("[" + std::to_string(i) + "]"),
										  s_Data.ModelMatrices[i]);
		}
		RenderCommand::DrawIndexed(s_Data.VertexArray,
								   (uint32_t)s_Data.IndexCount);

		s_Stats.DrawCalls++;
	}

	Renderer::Statistics Renderer::GetStats()
	{
		return s_Stats;
	}

	void Renderer::ResetStats()
	{
		memset(&s_Stats, 0, sizeof(Statistics));
	}

	void Renderer::DrawTriangle(const glm::vec4& color,
								const glm::mat4& model)
	{
		static std::vector<Renderer::Vertex> vertices =
		{
			{{-0.5f, -0.5f, 0.0f},	{0.0f, 0.0f}, 0, 0, color},
			{{ 0.5f, -0.5f, 0.0f},	{1.0f, 0.0f}, 0, 0, color},
			{{ 0.0f,  0.5f, 0.0f},	{0.5f, 1.0f}, 0, 0, color}
		};

		static std::vector<uint32_t> indices =
		{
			0, 1, 2
		};

		if (s_Data.IndexCount >= Util::MaxIndicesCount						||
			(s_Data.IndexCount + indices.size()) >= Util::MaxIndicesCount	||
			s_Data.TextureSlotIndex >= Util::MaxTexturesCount				||
			s_Data.ModelsCount >= Util::MaxModelMatricesCount				||
			s_Data.IndexOffset >= Util::MaxVerticesCount					||
			s_Data.IndexOffset + vertices.size() >= Util::MaxVerticesCount)
			NextBatch();

		if (s_Data.IndexCount == 0)
		{
			indices[0] = 0;
			indices[1] = 1;
			indices[2] = 2;
		}

		for (auto& ver : vertices)
			ver.ModelIndex = (int32_t)s_Data.ModelsCount, ver.Color = color;

		for (auto& idx : indices)
			idx = (uint32_t)s_Data.IndexOffset + idx;

		s_Data.VertexBuffer->Bind();
		s_Data.VertexBuffer->SetData(vertices.data(),
									 (vertices.size() * sizeof(Renderer::Vertex)),
									 (s_Data.IndexOffset * sizeof(Renderer::Vertex)));

		s_Data.IndexBuffer->Bind();
		s_Data.IndexBuffer->SetData(indices.data(),
									(uint32_t)indices.size(),
									(uint32_t)s_Data.IndexCount);

		s_Data.IndexCount += indices.size();
		s_Data.IndexOffset += vertices.size();

		s_Data.ModelMatrices[(uint32_t)s_Data.ModelsCount] = model;
		s_Data.ModelsCount++;

		s_Stats.TotalVertices += (uint32_t)s_Data.IndexOffset;
		s_Stats.TotalIndices  += (uint32_t)s_Data.IndexCount;
		s_Stats.ModelCount++;
	}

	void Renderer::DrawMesh(const MeshComponent& mesh,
							const glm::mat4& model)
	{
		size_t numOfVertices = mesh.Vertices.size();
		size_t numOfIndices = mesh.Indices.size();

		if (s_Data.IndexCount >= Util::MaxIndicesCount					||
			(s_Data.IndexCount + numOfIndices) >= Util::MaxIndicesCount ||
			s_Data.TextureSlotIndex >= Util::MaxTexturesCount			||
			s_Data.ModelsCount >= Util::MaxModelMatricesCount			||
			s_Data.IndexOffset >= Util::MaxVerticesCount				||
			(s_Data.IndexOffset + numOfVertices) >= Util::MaxVerticesCount)
			NextBatch();

		auto tempMesh = mesh;
		uint32_t textureSlot = 0;

		for (auto& tex : tempMesh.Textures)
		{
			bool alreadyAdded = false;
			for (uint32_t j = 1; j < s_Data.TextureSlotIndex; j++)
			{
				if (tex == s_Data.Textures[j])
				{
					textureSlot = j;
					alreadyAdded = true;
					break;
				}
			}

			if (!alreadyAdded)
			{
				s_Data.Textures[s_Data.TextureSlotIndex] = tex;
				textureSlot = s_Data.TextureSlotIndex;
				s_Data.TextureSlotIndex++;
			}
		}

		for (auto& vertex : tempMesh.Vertices)
			vertex.ModelIndex = s_Data.ModelsCount,
			vertex.TexIndex = textureSlot;

		for (auto& idx : tempMesh.Indices)
			idx = s_Data.IndexOffset + idx;

		s_Data.VertexBuffer->Bind();
		s_Data.VertexBuffer->SetData(tempMesh.Vertices.data(),
									 (numOfVertices * sizeof(Renderer::Vertex)),
									 (s_Data.IndexOffset * sizeof(Renderer::Vertex)));

		s_Data.IndexBuffer->Bind();
		s_Data.IndexBuffer->SetData(tempMesh.Indices.data(),
									(uint32_t)numOfIndices,
									(uint32_t)s_Data.IndexCount);

		s_Data.IndexOffset += numOfVertices;
		s_Data.IndexCount += numOfIndices;

		s_Data.ModelMatrices[(uint32_t)s_Data.ModelsCount] = model;
		s_Data.ModelsCount++;

		s_Stats.TotalVertices += (uint32_t)s_Data.IndexOffset;
		s_Stats.TotalIndices += (uint32_t)s_Data.IndexCount;
		s_Stats.ModelCount++;
	}
}

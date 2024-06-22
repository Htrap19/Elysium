#pragma once

#include "renderer/vertexarray.h"
#include "renderer/shader.h"

#include <glm/glm.hpp>

namespace Elysium
{
	struct MeshComponent;

	class Renderer
	{
	public:
		struct Statistics
		{
			uint32_t DrawCalls		= 0;
			uint32_t TotalVertices	= 0;
			uint32_t TotalIndices	= 0;
			uint32_t ModelCount		= 0;
		};

		struct Vertex
		{
			glm::vec3 Position	= glm::vec3(0.0f);
			glm::vec2 TexCoord	= glm::vec2(0.0f);
			int TexIndex		= 0;
			int ModelIndex		= 0;
			glm::vec4 Color		= glm::vec4(1.0f);
		};

	public:
		static void Init();

		static void Begin(const glm::mat4& projection,
						  const glm::mat4& view);
		static void End();
		static void Flush();

		static Statistics GetStats();
		static void ResetStats();

		static void DrawTriangle(const glm::vec4& color,
								 const glm::mat4& model = glm::mat4(1.0f));

		static void DrawMesh(const MeshComponent& mesh,
							 const glm::mat4& model = glm::mat4(1.0f));

	private:
		inline static Statistics s_Stats;
	};
}
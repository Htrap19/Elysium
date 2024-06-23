#pragma once

#include "renderer/renderer.h"

#include "scene/assimploader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Elysium
{
	struct TransformComponent
	{
		glm::vec3 Position	= glm::vec3(0.0f);
		glm::vec3 Rotate	= glm::vec3(0.0f);
		glm::vec3 Scale		= glm::vec3(1.0f);

		glm::mat4 GetTransform() const
		{
			auto rotation = glm::toMat4(glm::quat(Rotate));
			glm::mat4 model = glm::translate(glm::mat4(1.0f), Position)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);

			return model;
		}
	};

	struct MeshComponent
	{
		std::vector<Renderer::Vertex> Vertices;
		std::vector<uint32_t> Indices;
		std::vector<Shared<Texture2D>> Textures;

		MeshComponent(const std::string& file)
		{
			AssimpLoader loader;
			loader.Load(file);

			auto& entries = loader.GetMeshEntries();

			for (auto& mesh : entries)
			{
				Vertices.insert(Vertices.end(),
								mesh.Vertices.begin(),
								mesh.Vertices.end());

				Indices.insert(Indices.end(),
							   mesh.Indices.begin(),
							   mesh.Indices.end());

				Textures.insert(Textures.end(),
								mesh.Textures.begin(),
								mesh.Textures.end());
			}
		}
	};
}
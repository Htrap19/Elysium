#pragma once

#include "renderer/renderer.h"

#include "scene/assimploader.h"
#include "scene/camera.h"
#include "scene/scriptableentity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <string.h>

namespace Elysium
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent(const std::string& tag)
			: Tag(tag)
		{}
	};

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

		std::string Path;

		MeshComponent(const std::string& file)
			: Path(file)
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

	struct CameraComponent
	{
		Camera Camera;
		bool IsPrimary;

		CameraComponent(const glm::vec3& position,
						bool isPrimary = true)
			: Camera(position, 0.0f, 0.0f, 25.0f, 0.5f),
			IsPrimary(isPrimary)
		{}
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)() = nullptr;
		void (*DestroyScript)(NativeScriptComponent*) = nullptr;

		template <typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}

		template <typename T>
		T* As()
		{
			return static_cast<T*>(Instance);
		}
	};
}
#include "scene.h"

#include "scene/entity.h"
#include "scene/components.h"

#include "renderer/renderer.h"
#include "renderer/rendercommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Elysium
{
	Scene::Scene()
	{
		m_AspectRatio = ((float)1280 / (float)720);
	}

	Entity Scene::CreateEntity()
	{
		auto entity = Entity(m_Registry.create(), this);
		entity.AddComponent<TransformComponent>();

		return entity;
	}

	void Scene::OnUpdate()
	{
		auto view = m_Registry.view<TransformComponent, MeshComponent>();

		auto projMat = glm::perspective(glm::radians(60.0f),
										m_AspectRatio,
										0.1f,
										100.0f);

		auto viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
								   glm::vec3(0.0f),
								   glm::vec3(0.0f, 1.0f, 0.0f));
		Renderer::Begin(projMat, viewMat);
		for (auto& entity : view)
		{
			auto& transform = view.get<TransformComponent>(entity);
			auto& mesh = view.get<MeshComponent>(entity);
			Renderer::DrawMesh(mesh, transform.GetTransform());
		}
		Renderer::End();
	}

	void Scene::Resize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
		m_AspectRatio = (float)width / (float)height;
	}
}
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

	Scene::~Scene()
	{
		m_Registry.view<NativeScriptComponent>().each([](auto entity, NativeScriptComponent& nsc)
			{
				nsc.Instance->OnDestroy();
				nsc.DestroyScript(&nsc);
			});
	}

	Entity Scene::CreateEntity()
	{
		auto entity = Entity(m_Registry.create(), this);
		entity.AddComponent<TransformComponent>();

		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		m_Registry.view<NativeScriptComponent>().each([&](auto entity, auto& nsc)
			{
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->OnCreate();
					nsc.Instance->m_Self = Entity(entity, this);
				}

				nsc.Instance->OnUpdate(ts);
			});

		glm::mat4 projMat = glm::mat4(1.0f);
		glm::mat4 viewMat = glm::mat4(1.0f);

		auto cameraRegistryView = m_Registry.view<CameraComponent>();

		Camera primaryCamera;
		for (auto& entity : cameraRegistryView)
		{
			auto& cameraComponent = cameraRegistryView.get<CameraComponent>(entity);
			if (cameraComponent.IsPrimary)
			{
				primaryCamera = cameraComponent.Camera;
				break;
			}
		}

		viewMat = primaryCamera.CalculateView();
		projMat = primaryCamera.CalculateProjection();

		if (m_SkyBox)
		{
			Renderer::DrawSkyBox(projMat,
								 glm::mat4(glm::mat3(viewMat)),
								 m_SkyBox);
		}

		auto view = m_Registry.view<TransformComponent, MeshComponent>();

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
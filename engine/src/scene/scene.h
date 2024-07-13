#pragma once

#include <entt/entt.hpp>

#include "core/timestep.h"

#include "renderer/shader.h"
#include "renderer/vertexarray.h"
#include "renderer/texture.h"

class SceneHierarchicalPanel;

namespace Elysium
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		Entity CreateEntity(const std::string& name = "");

		inline void SetSkyBox(const Shared<CubeMap>& skybox)
		{ m_SkyBox = skybox; }

		void OnUpdate(Timestep ts);

		void Resize(uint32_t width, uint32_t height);

		inline float GetAspectRatio() const
		{ return m_AspectRatio; }

	private:
		entt::registry m_Registry;
		Shared<CubeMap> m_SkyBox;

		float m_AspectRatio = 0.0f;

		friend class Entity;
		friend class SceneHierarchicalPanel;
	};
}
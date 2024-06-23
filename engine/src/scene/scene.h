#pragma once

#include <entt/entt.hpp>

#include "renderer/shader.h"
#include "renderer/vertexarray.h"
#include "renderer/texture.h"

namespace Elysium
{
	class Entity;
	class Scene
	{
	public:
		Scene();

		Entity CreateEntity();

		inline void SetSkyBox(const Shared<CubeMap>& skybox)
		{ m_SkyBox = skybox; }

		void OnUpdate();

		void Resize(uint32_t width, uint32_t height);

	private:
		entt::registry m_Registry;
		Shared<CubeMap> m_SkyBox;

		float m_AspectRatio = 0.0f;

		friend class Entity;
	};
}
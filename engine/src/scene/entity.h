#pragma once

#include "core/log.h"

#include "scene/scene.h"

namespace Elysium
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity entity, Scene* scene);

		inline bool IsValid() const
		{
			return m_Scene->m_Registry.valid(m_EnttHandle);
		}

		template <typename T, typename ... Args>
		T& AddComponent(Args&& ... args)
		{
			if (HasComponent<T>())
			{
				ES_CORE_ERROR("Component already exists!");
				return m_Scene->m_Registry.get<T>(m_EnttHandle);
			}
			return m_Scene->m_Registry.emplace<T>(m_EnttHandle, args...);
		}

		template <typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_EnttHandle);
		}

		template <typename T>
		void RemoveComponent()
		{
			if (!HasComponent<T>())
			{
				ES_CORE_ERROR("Error while removing component: Component not exists!");
				return;
			}
			m_Scene->m_Registry.remove<T>(m_EnttHandle);
		}

		template <typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry.get<T>(m_EnttHandle);
		}

		inline Scene* GetScene() const
		{ return m_Scene; }

	private:
		entt::entity m_EnttHandle = entt::null;
		Scene* m_Scene = nullptr;
	};
}
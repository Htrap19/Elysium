#pragma once

#include "core/timestep.h"

#include "scene/entity.h"

namespace Elysium
{
	class Scene;
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() = default;

	protected:
		virtual void OnCreate() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnDestroy() {}

	protected:
		Entity m_Self;

		friend class Scene;
	};
}
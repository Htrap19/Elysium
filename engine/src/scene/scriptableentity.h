#pragma once

#include "core/timestep.h"

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

	private:
		friend class Scene;
	};
}
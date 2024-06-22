#include "entity.h"

namespace Elysium
{
	Entity::Entity(entt::entity entity, Scene* scene)
		: m_EnttHandle(entity),
		m_Scene(scene)
	{
	}
}
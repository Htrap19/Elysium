#pragma once

#include "core/keycodes.h"
#include "core/mousecodes.h"

#include <glm/glm.hpp>

namespace Elysium
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode key);
		static glm::vec2 GetCursorPosition();
		static float GetCursorX();
		static float GetCursorY();
	};
}
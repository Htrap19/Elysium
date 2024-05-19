#pragma once

#include "core/utility.h"

struct GLFWwindow;
namespace Elysium
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init()			= 0;
		virtual void SwapBuffers()	= 0;

		static Unique<GraphicsContext> Create(GLFWwindow* window);
	};
}
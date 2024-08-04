#ifdef ES_PLATFORM_UNIX

#include "core/input.h"

#include "core/application.h"

#include <GLFW/glfw3.h>

namespace Elysium
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		return glfwGetKey((GLFWwindow*)Application::GetInstance()
									.GetWindow()
									.GetNativeWindow(), 
						  key) == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(MouseCode key)
	{
		return glfwGetMouseButton((GLFWwindow*)Application::GetInstance()
									.GetWindow()
									.GetNativeWindow(),
								  key) == GLFW_PRESS;
	}

	glm::vec2 Input::GetCursorPosition()
	{
		double xpos, ypos;
		glfwGetCursorPos((GLFWwindow*)Application::GetInstance()
									.GetWindow()
									.GetNativeWindow(),
						 &xpos,
						 &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Input::GetCursorX()
	{
		return GetCursorPosition().x;
	}

	float Input::GetCursorY()
	{
		return GetCursorPosition().y;
	}
}

#endif

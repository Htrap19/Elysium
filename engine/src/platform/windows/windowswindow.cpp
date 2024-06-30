#ifdef ES_PLATFORM_WINDOWS

#include "windowswindow.h"

#include "core/log.h"
#include "event/applicationevent.h"
#include "event/keyevent.h"
#include "event/mouseevent.h"

#include <GLFW/glfw3.h>

namespace Elysium
{
	static uint32_t s_WindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		ES_CORE_ERROR("GLFW error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
		: m_Data{props.Width, props.Height, props.Title}
	{
		if (s_WindowCount <= 0)
		{
			if (!glfwInit())
			{
				ES_CORE_ERROR("Failed to initialize GLFW!");
				return;
			}
			s_WindowCount++;
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		m_Window = glfwCreateWindow((int)m_Data.Width,
									(int)m_Data.Height,
									m_Data.Title.c_str(),
									nullptr,
									nullptr);

		if (!m_Window)
		{
			ES_CORE_ERROR("Failed to create window!");
			return;
		}

		ES_CORE_INFO("Creating window ({0} {1}x{2})",
					 m_Data.Title,
					 m_Data.Width,
					 m_Data.Height);
		m_GraphicsContext = GraphicsContext::Create(m_Window);
		m_GraphicsContext->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		
		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window,
			[](GLFWwindow* window, int width, int height)
			{
				auto data = (WindowData*)(glfwGetWindowUserPointer(window));
				data->Width = width;
				data->Height = height;

				WindowResizeEvent e((uint32_t)width,
									(uint32_t)height);
				data->Callback(e);
			});

		glfwSetWindowCloseCallback(m_Window,
			[](GLFWwindow* window)
			{
				auto data = (WindowData*)(glfwGetWindowUserPointer(window));

				WindowCloseEvent e;
				data->Callback(e);
			});

		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto data = (WindowData*)(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data->Callback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data->Callback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1);
					data->Callback(e);
					break;
				}

				default:
					break;
				}
			});

		glfwSetMouseButtonCallback(m_Window,
			[](GLFWwindow* window, int key, int action, int mods)
			{
				auto data = (WindowData*)(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(key);
					data->Callback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(key);
					data->Callback(e);
					break;
				}

				default:
					break;
				}
			});

		glfwSetScrollCallback(m_Window,
			[](GLFWwindow* window, double xOffset, double yOffset)
			{
				auto data = (WindowData*)(glfwGetWindowUserPointer(window));
				
				MouseScrolledEvent e((float)xOffset,
									 (float)yOffset);
				data->Callback(e);
			});
		
		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double xpos, double ypos)
			{
				auto data = (WindowData*)(glfwGetWindowUserPointer(window));

				MouseMovedEvent e((float)xpos, (float)ypos);
				data->Callback(e);
			});

		glfwSetCharCallback(m_Window,
			[](GLFWwindow* window, unsigned int codepoint)
			{
				auto data = (WindowData*)(glfwGetWindowUserPointer(window));

				KeyTypedEvent e(codepoint);
				data->Callback(e);
			});
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		s_WindowCount--;

		if (s_WindowCount <= 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_GraphicsContext->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::SetCursorMode(bool enable)
	{
		glfwSetInputMode(m_Window,
						 GLFW_CURSOR,
						 (enable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED));
	}
}

#endif
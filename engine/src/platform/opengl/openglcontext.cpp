#include "openglcontext.h"

#include "core/log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Elysium
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window)
	{
		if (!m_WindowHandle)
		{
			ES_CORE_CRITICAL("Window handle is null!");
		}
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 0)
		{
			ES_CORE_ERROR("Failed to initialize OpenGL context!");
			return;
		}

		ES_CORE_INFO("OpenGL Info:");
		ES_CORE_INFO("\tVendor: {0}", (const char*)glGetString(GL_VENDOR));
		ES_CORE_INFO("\tRenderer: {0}", (const char*)glGetString(GL_RENDERER));
		ES_CORE_INFO("\tVersion: {0}", (const char*)glGetString(GL_VERSION));

		if (GLVersion.major < 3 && GLVersion.minor < 3)
		{
			ES_CORE_ERROR("Elysium requires atleast OpenGL version 3.3!");
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}

#pragma once

#ifdef ES_PLATFORM_WINDOWS

#include "core/window.h"
#include "renderer/graphicscontext.h"

struct GLFWwindow;

namespace Elysium
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		inline virtual uint32_t GetWidth() const override { return m_Data.Width; }
		inline virtual uint32_t GetHeight() const override { return m_Data.Height; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override
		{ m_Data.Callback = callback; }

		inline virtual void* GetNativeWindow() const override { return m_Window; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

	private:


	private:
		GLFWwindow* m_Window = nullptr;
		Unique<GraphicsContext> m_GraphicsContext;

		struct WindowData
		{
			uint32_t Width, Height;
			std::string Title;
			bool VSync;

			EventCallbackFn Callback;
		} m_Data;
	};
}

#endif
#pragma once

#include "event/event.h"

#include <functional>

namespace Elysium
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;

		WindowProps(const std::string& title = "Elysium",
					uint32_t width = 1280,
					uint32_t height = 720)
			: Title(title),
			Width(width),
			Height(height)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const  = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& func) = 0;
		virtual void* GetNativeWindow() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Unique<Window> Create(const WindowProps& props = WindowProps());
	};
}
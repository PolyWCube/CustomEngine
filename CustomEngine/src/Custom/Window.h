#pragma once

#include "CustomPrecompileHeader.h"

#include "Custom/Base.h"
#include "Custom/Event/Event.h"

namespace Custom {
	struct WindowProp {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProp(const std::string& title = "Custom", unsigned int width = 1280, unsigned int height = 720) : title(title), height(height), width(width) {}
	};
	
	class Window {
	public :
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProp& prop = WindowProp());
	};
}
#pragma once

#include "Custom/Window.h"
#include "GLFW/glfw3.h"

namespace Custom {
	class WindowsWindow : public Window {
	public :
		WindowsWindow(const WindowProp& prop);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return data.width; }
		inline unsigned int GetHeight() const override { return data.height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { data.eventCallback = callback; }
		void SetVSync(bool enable) override;
		bool IsVSync() const override;
	private :
		virtual void Init(const WindowProp& prop);
		virtual void ShutDown();

		GLFWwindow* window;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool VSync;

			EventCallbackFn eventCallback;
		};

		WindowData data;
	};
}


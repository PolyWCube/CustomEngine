#include "CustomPrecompileHeader.h"
#include "WindowsWindow.h"

#include "Custom/Event/ApplicationEvent.h"
#include "Custom/Event/MouseEvent.h"
#include "Custom/Event/KeyEvent.h"

namespace Custom {
	static bool GLFWInit = false;

	static void GLFWErrorCallback(int error, const char* description) {
		LOG_ENGINE_ERROR("GLFW occurred ", error, " : ", description)
	}

	Window* Window::Create(const WindowProp& prop) { return new WindowsWindow(prop); }

	WindowsWindow::WindowsWindow(const WindowProp& prop) { Init(prop); }

	WindowsWindow::~WindowsWindow() {
		ShutDown();
	}
	
	void WindowsWindow::Init(const WindowProp& prop) {
		data.title = prop.title;
		data.width = prop.width;
		data.height = prop.height;

		LOG_BREAK
		LOG_ENGINE_INFO("Window generation : ", prop.title)
		LOG_ENGINE_INFO("     Target platform : Windows")
		LOG_ENGINE_INFO("     Graphical library : GLFW")
		LOG_ENGINE_INFO("     Size : ", prop.width, "x", prop.height)
		LOG_BREAK
		LOG_ENGINE_INFO("     Initialize GLFW...")

		if (!GLFWInit) {
			int success = glfwInit();
			
			LOG_ENGINE_ASSERT(success, "     Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFWInit = true;
			LOG_ENGINE_SUCCESS("     GLFW initialized!")
		}

		window = glfwCreateWindow((int)prop.width, (int)prop.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.eventCallback(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS : {
					KeyPressEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE : {
					KeyReleaseEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT : {
					KeyPressEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS : {
					MouseButtonPressEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE : {
					MouseButtonReleaseEvent event(button);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrollEvent event((float)xOffset, (float)yOffset);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPosition, double yPosition) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMoveEvent event((float)xPosition, (float)yPosition);
			data.eventCallback(event);
			});

		LOG_BREAK
		LOG_SUCCESS("Window initialized!")
	}

	void WindowsWindow::ShutDown() {
		glfwDestroyWindow(window);
	}
	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	void WindowsWindow::SetVSync(bool enable) {
		glfwSwapInterval(enable ? 1 : 0);
		data.VSync = enable;
	}
	bool WindowsWindow::IsVSync() const { return data.VSync; }
}
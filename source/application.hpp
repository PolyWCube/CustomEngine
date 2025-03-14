#ifndef CUSTOM_APPLICATION
#define CUSTOM_APPLICATION

#include "base.hpp"
#include "component/graphic/window.hpp"
#include "utility/event.hpp"
#include "utility/event/window.hpp"

namespace Custom {
	class Application {
	public :
		Application();
		virtual ~Application();

		void Run();

		void Event(Event::Event& event);
	private :
		bool WindowClose(Event::WindowClose& event);

		bool run = true;
		std::unique_ptr<Graphic::Window::Window> window;
	};

	Application* createApplication();
}

#endif
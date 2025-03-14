#include "precompiledheader.hpp"

#include "application.hpp"
#include "component/log.hpp"
#include "utility/math/vector.hpp"

namespace Custom {
	#define BIND_EVENT_CALLBACK(function) std::bind(&Application::function, this, std::placeholders::_1)

	Application::Application() {
		Log::Initial();
		window = std::unique_ptr<Graphic::Window::Window>(Graphic::Window::Window::Create());
		window->SetEventCallback(BIND_EVENT_CALLBACK(Event));
		window->Show();
	}
	Application::~Application() {}

	void Application::Run() {
		while (run) {
			window->Update();
		}
	}

	void Application::Event(Event::Event& event) {
		Event::Manager eventManager(event);
		eventManager.Dispatch<Event::WindowClose>(BIND_EVENT_CALLBACK(WindowClose));

		Log::Trace(event);
	}

	bool Application::WindowClose(Event::WindowClose& event) {
		run = false;
		return true;
	}
}
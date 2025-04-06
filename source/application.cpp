#include "precompiled_header.hpp"

#include "application.hpp"
#include "utility/log/log.hpp"
#include "utility/math/math.hpp"

namespace Custom {
	#define BIND_EVENT_CALLBACK(function) std::bind(&Application::function, this, std::placeholders::_1)

	Application::Application() {
		Log::Initial();
	}
	Application::~Application() {}

	void Application::Run() {
		Object::ID windowID = objectManager.CreateObject();
		objectManager.AddProperty<Object::Window>(windowID);
		objectManager.GetProperty<Object::Window>(windowID)->Create();

		Graphic::Window::Window* window = objectManager.GetProperty<Object::Window>(windowID)->GetWindow();
		if (window) {
			window->SetVisible(true);
			window->SetEventCallback(BIND_EVENT_CALLBACK(Event));
		}

		while (run) {
			for (Layer::Layer* layer : layerManager) layer->Update();
			window->Update();
		}
	}

	void Application::Event(Event::Event& event) {
		Event::Manager eventManager(event);
		eventManager.Dispatch<Event::WindowClose>(BIND_EVENT_CALLBACK(WindowClose));

		for (auto it = layerManager.end(); it != layerManager.begin(); ) {
			(*--it)->Event(event);
			if (event.handle) break;
		}
	}

	void Application::AddLayer(Layer::Layer* layer) {
		layerManager.AddLayer(layer);
	}
	void Application::AddOverlay(Layer::Layer* overlay) {
		layerManager.AddOverlay(overlay);
	}

	bool Application::WindowClose(Event::WindowClose& event) {
		run = false;
		return true;
	}
}
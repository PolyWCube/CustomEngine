#ifndef CUSTOM_APPLICATION
#define CUSTOM_APPLICATION

#include "base.hpp"

#include "utility/event/window.hpp"
#include "utility/layer/manager.hpp"
#include "utility/object/manager.hpp"

namespace Custom {
	class Application {
	public :
		Application();
		virtual ~Application();

		void Run();

		void Event(Event::Event& event);

		void AddLayer(Layer::Layer* layer);
		void AddOverlay(Layer::Layer* overlay);
	private :
		bool WindowClose(Event::WindowClose& event);

		bool run = true;

		Object::Manager objectManager;
		Layer::Manager layerManager;
	};

	Application* createApplication();
}

#endif
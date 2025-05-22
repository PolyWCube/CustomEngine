#ifndef CUSTOM_APPLICATION
#define CUSTOM_APPLICATION

#include "base.hpp"

#include "component/user_interface/button.hpp"
#include "utility/event/window.hpp"
#include "utility/layer/manager.hpp"
#include "utility/object/manager.hpp"
#include "utility/helper/benchmark.hpp"
#include "utility/helper/draw.hpp"

namespace Custom {
	#define BIND_EVENT_CALLBACK(function) std::bind(&function, this, std::placeholders::_1)

	class Application {
	public :
		Application();
		virtual ~Application();

		void Run();
		void Shutdown();
		void Minimize();
		void Resize();
		void Event(Event::Event& event);

		void AddLayer(Layer::Layer* layer);
		void AddOverlay(Layer::Layer* overlay);
	private :
		bool run;

		Layer::Manager layerManager;
		UI::Manager uiManager;

		Object::Object* object;
		Object::Window* windowProperty;
		Object::Renderer* rendererProperty;

		Graphic::Window::Window* window;
		Object::DynamicBuffer<Graphic::RGBAColor<uint8_t, float>> buffer;

	};

	Application* CreateApplication();
}

#endif
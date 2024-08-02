#pragma once
#include "Custom/Base.h"
#include "Custom/Window.h"
#include "Custom/Event/Event.h"
#include "Custom/Event/ApplicationEvent.h"
#include "Custom/Layer/LayerStack.h"

namespace Custom {
	class Application {
	public :
		Application();
		virtual ~Application();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();
	private :
		std::unique_ptr<Window> window;
		LayerStack layerStack;

		bool run = false;

		bool OnWindowClose(WindowCloseEvent& event);
	};
	Application* GenerateApplication();
}
#include "CustomPrecompileHeader.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"

namespace Custom {
	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application() {
		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		run = true;
	}
	Application::~Application() {

	}

	void Application::OnEvent(Event& event) {
		EventDispatch dispatch(event);
		dispatch.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (std::vector<Layer*>::iterator iterator = layerStack.end(); iterator != layerStack.begin();) {
			(*--iterator)->OnEvent(event);
			if (event.handle) break;
		}
	}

	void Application::PushLayer(Layer* layer) { layerStack.PushLayer(layer); }
	void Application::PushOverlay(Layer* overlay) { layerStack.PushOverlay(overlay); }

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		run = false;
		return true;
	}
	
	void Application::Run() {

		while (run)
		{
			for (Layer* layer : layerStack) {
				std::cout << layer->GetName();
				layer->OnUpdate();
			}
			window->OnUpdate();
		}
	}
}
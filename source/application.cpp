#include "precompiled_header.hpp"
#include "component/graphic/renderer/renderer.hpp"
#include "utility/object/buffer.hpp"

#include "application.hpp"
#include "utility/log/log.hpp"
#include "component/graphic/color.hpp"


#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_SIZE WINDOW_WIDTH * WINDOW_HEIGHT

namespace Custom {
	Application::Application() : run(true), object(new Object::Object()), buffer(WINDOW_SIZE) {
		Log::Initial();
		AddLayer(new UI::Layer(uiManager));

		buffer.SetDataAll({ 0, 0, 0, 255 });

		object->AddProperty<Object::Window>();
		windowProperty = object->GetProperty<Object::Window>();
		windowProperty->Create();
		window = windowProperty->Get();

		object->AddProperty<Object::Renderer>();
		rendererProperty = object->GetProperty<Object::Renderer>();

		if (window) {
			window->SetVisible(true);
			window->SetEventCallback(BIND_EVENT_CALLBACK(Event));

			rendererProperty->Create(window->GetWindowHandle());
		}
		/*
		Utility::Benchmark<Utility::microsecond> renderBenchmark([this]() { Run(); });
		size_t renderIterations = 60;
		renderBenchmark.Run(renderIterations);
		Log::Debug("Render Size:", WINDOW_WIDTH, ", ", WINDOW_HEIGHT);
		Log::Debug("Benchmark of Render() for ", renderIterations, " iterations:");
		Log::Debug("Total duration: ", renderBenchmark.duration().count(), " microseconds");
		*/
		std::unique_ptr<UI::Button> closeButton = std::make_unique<UI::Button>("closeButton", 0, Math::Vector3<int16_t>(10, 10, 0), Math::Vector2<uint16_t>(40, 40));
		std::unique_ptr<UI::Button> resizeButton = std::make_unique<UI::Button>("resizeButton", 1, Math::Vector3<int16_t>(60, 10, 0), Math::Vector2<uint16_t>(40, 40));
		std::unique_ptr<UI::Button> minimizeButton = std::make_unique<UI::Button>("minimizeButton", 2, Math::Vector3<int16_t>(110, 10, 0), Math::Vector2<uint16_t>(40, 40));

		closeButton->SetDefaultColor({150, 0, 0, 255});
		closeButton->SetHoverColor({250, 0, 0, 255});
		closeButton->SetPressColor({50, 0, 0, 255});
		closeButton->SetDisableColor({50, 0, 0, 255});

		resizeButton->SetDefaultColor({0, 150, 0, 255});
		resizeButton->SetHoverColor({0, 250, 0, 255});
		resizeButton->SetPressColor({0, 50, 0, 255});
		resizeButton->SetDisableColor({0, 50, 0, 255});

		minimizeButton->SetDefaultColor({0, 0, 150, 255});
		minimizeButton->SetHoverColor({0, 0, 250, 255});
		minimizeButton->SetPressColor({0, 0, 50, 255});
		minimizeButton->SetDisableColor({0, 0, 50, 255});

		closeButton->SetClickCallback([this]() { Shutdown(); });
		resizeButton->SetClickCallback([this]() { Resize(); });
		minimizeButton->SetClickCallback([this]() { Minimize(); });

		uiManager.AddElement(std::move(closeButton));
		uiManager.AddElement(std::move(resizeButton));
		uiManager.AddElement(std::move(minimizeButton));
	}
	Application::~Application() {
		delete window;
		delete object;
	}

	void Application::Run() {
		while (run) {
			for (Layer::Layer* layer : layerManager) layer->Update();
			window->Update();

			Graphic::Draw::FillRectangle(buffer, { WINDOW_WIDTH, WINDOW_HEIGHT }, {0, 0}, { WINDOW_WIDTH, 60 }, {150, 150, 150, 255});
			uiManager.UpdateBuffer(buffer, { WINDOW_WIDTH, WINDOW_HEIGHT });

			rendererProperty->BeginFrame();
			rendererProperty->SetBuffer(buffer.GetDatas(), WINDOW_WIDTH, WINDOW_HEIGHT);
			rendererProperty->SwapBuffer();
			rendererProperty->EndFrame();
		}
	}
	void Application::Shutdown() {
		run = false;
	}
	void Application::Minimize() {
		window = windowProperty->Get();
		window->Minimize();
	}
	void Application::Resize() {
		window = windowProperty->Get();
		if (window->IsMaximize()) window->Restore();
		else window->Maximize();
	}
	void Application::Event(Event::Event& event) {
		//Event::Manager eventManager(event);

		for (auto iterator = layerManager.end(); iterator != layerManager.begin();) {
			(*--iterator)->Event(event);
			if (event.handle) break;
		}
	}

	void Application::AddLayer(Layer::Layer* layer) {
		layerManager.AddLayer(layer);
	}
	void Application::AddOverlay(Layer::Layer* overlay) {
		layerManager.AddOverlay(overlay);
	}
}
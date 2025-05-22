#include "../include/custom.hpp"

using namespace Custom;

class AppLayer : public Layer::Layer {
public :
	AppLayer() : Layer("Application") {}
	void Update() override {}
	void Event(Event::Event& event) override {}
};

class App : public Application {
public :
	App() {
		AppLayer* appLayer = new AppLayer();
		AddLayer(appLayer);
	}
	~App() {}
};

Application* Custom::CreateApplication() {
	return new App();
}
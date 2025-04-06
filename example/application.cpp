#include "../include/custom.hpp"

class AppLayer : public Custom::Layer::Layer {
public :
	AppLayer() : Layer("Application") {}
	void Update() override {}
	void Event(Custom::Event::Event& event) override {}
};

class App : public Custom::Application {
public :
	App() {
		AddLayer(new AppLayer());
	}
	~App() {}
};

Custom::Application* Custom::createApplication() {
	return new App();
}
#include <Custom.h>

class ApplicationLayer : public Custom::Layer {
public :
	ApplicationLayer() : Layer("Debug") {}

	void OnUpdate() override {
		LOG_INFO("Application layer update")
	}
	void OnEvent(Custom::Event& event) override {
		LOG_TRACE(event);
	}
};
class Application : public Custom::Application {
public :
	Application() {
		PushLayer(new ApplicationLayer());
	}
	~Application() {

	}
};

Custom::Application* Custom::GenerateApplication() {
	return new Application();
}
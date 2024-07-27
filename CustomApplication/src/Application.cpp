#include <Custom.h>

class Application : public Custom::Application {
public :
	Application() {

	}
	~Application() {

	}
};

Custom::Application* Custom::GenerateApplication() {
	return new Application();
}
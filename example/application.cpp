#include "../include/custom.hpp"

class App : public Custom::Application {
public :
	App() {}
	~App() {}
};

Custom::Application* Custom::createApplication() {
	return new App();
}
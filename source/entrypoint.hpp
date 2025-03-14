#ifndef CUSTOM_ENTRYPOINT
#define CUSTOM_ENTRYPOINT

#include "application.hpp"

#ifdef CUSTOM_PLATFORM_WINDOWS

extern Custom::Application* Custom::createApplication();
//int argc, char** argv
int main() {
	auto app = Custom::createApplication();
	app->Run();
	delete app;
}

#endif

#endif
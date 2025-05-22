#ifndef CUSTOM_ENTRYPOINT
#define CUSTOM_ENTRYPOINT

#include "application.hpp"

#ifdef CUSTOM_PLATFORM_WINDOWS

extern Custom::Application* Custom::CreateApplication();

int main(int argc, char** argv) {
	auto app = Custom::CreateApplication();
	app->Run();
	delete app;
}

#endif

#endif
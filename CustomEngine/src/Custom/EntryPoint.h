#pragma once

#ifdef CUSTOM_PLATFORM_WINDOWS

extern Custom::Application* Custom::GenerateApplication();

int main(int argc, char** argv) {
	Custom::Log::Init();

	auto app = Custom::GenerateApplication();
	app->Run();
	delete app;
}
#endif
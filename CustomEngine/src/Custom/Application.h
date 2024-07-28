#pragma once

namespace Custom {
	class Application {
	public :
		Application();
		virtual ~Application();

		void Run();
	};
	Application* GenerateApplication();
}


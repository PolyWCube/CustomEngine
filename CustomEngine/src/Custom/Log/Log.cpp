#include "Log.h"

namespace Custom {
	std::shared_ptr<Custom::Logger> Log::engineLogger;
	std::shared_ptr<Custom::Logger> Log::applicationLogger;
	void Log::Init() {
		engineLogger =std::make_shared<Custom::Logger>("[Engine]      ", Custom::LogColor::red);
		applicationLogger = std::make_shared<Custom::Logger>("[Application] ", Custom::LogColor::red);

	}
}
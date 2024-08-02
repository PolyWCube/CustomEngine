#include "CustomPrecompileHeader.h"
#include "Log.h"

namespace Custom {
	std::shared_ptr<Custom::Logger> Log::engineLogger;
	std::shared_ptr<Custom::Logger> Log::applicationLogger;

	void Log::Init() {
		engineLogger = std::make_shared<Custom::Logger>("[Engine]      ", Custom::LogColor::red);
		applicationLogger = std::make_shared<Custom::Logger>("[Application] ", Custom::LogColor::blue);
		LOG_ENGINE_INFO("Initialize logging system...")

		LOG_ENGINE_SUCCESS("Logging system initialized!")
	}
}
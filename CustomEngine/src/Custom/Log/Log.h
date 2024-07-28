#pragma once

#include <memory>

#include "../Base.h"
#include "CustomLog.cpp"

namespace Custom {
	class Log
	{
	public :
		static void Init();

		inline static std::shared_ptr<Custom::Logger>& GetEngineLogger() { return engineLogger; }
		inline static std::shared_ptr<Custom::Logger>& GetApplicationLogger() { return applicationLogger; }
	private :
		static std::shared_ptr<Custom::Logger> engineLogger;
		static std::shared_ptr<Custom::Logger> applicationLogger;
	};
}

#define LOG_ENGINE_TRACE(...)	Custom::GetEngineLogger()->Log(Custom::LogMode::trace,			Custom::LogColor::white,		__VA_ARGS__)
#define LOG_ENGINE_INFO(...)	Custom::GetEngineLogger()->Log(Custom::LogMode::info,			Custom::LogColor::green,		__VA_ARGS__)
#define LOG_ENGINE_SUCCESS(...)	Custom::GetEngineLogger()->Log(Custom::LogMode::success,		Custom::LogColor::boldGreen,	__VA_ARGS__)
#define LOG_ENGINE_DEBUG(...)	Custom::GetEngineLogger()->Log(Custom::LogMode::debug,			Custom::LogColor::blue,			__VA_ARGS__)
#define LOG_ENGINE_WARN(...)	Custom::GetEngineLogger()->Log(Custom::LogMode::warn,			Custom::LogColor::yellow,		__VA_ARGS__)
#define LOG_ENGINE_ERROR(...)	Custom::GetEngineLogger()->Log(Custom::LogMode::error,			Custom::LogColor::magenta,		__VA_ARGS__)
#define LOG_ENGINE_FATAL(...)	Custom::GetEngineLogger()->Log(Custom::LogMode::fatal,			Custom::LogColor::red,			__VA_ARGS__)

#define LOG_TRACE(...)			Custom::GetApplicationLogger()->Log(Custom::LogMode::trace,		Custom::LogColor::white,		__VA_ARGS__)
#define LOG_INFO(...)			Custom::GetApplicationLogger()->Log(Custom::LogMode::info,		Custom::LogColor::green,		__VA_ARGS__)
#define LOG_SUCCESS(...)		Custom::GetApplicationLogger()->Log(Custom::LogMode::success,	Custom::LogColor::boldGreen,	__VA_ARGS__)
#define LOG_DEBUG(...)			Custom::GetApplicationLogger()->Log(Custom::LogMode::debug,		Custom::LogColor::blue,			__VA_ARGS__)
#define LOG_WARN(...)			Custom::GetApplicationLogger()->Log(Custom::LogMode::warn,		Custom::LogColor::yellow,		__VA_ARGS__)
#define LOG_ERROR(...)			Custom::GetApplicationLogger()->Log(Custom::LogMode::error,		Custom::LogColor::magenta,		__VA_ARGS__)
#define LOG_FATAL(...)			Custom::GetApplicationLogger()->Log(Custom::LogMode::fatal,		Custom::LogColor::red,			__VA_ARGS__)
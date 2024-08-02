#pragma once

#include "CustomLog.cpp"
#include "Custom/Base.h"

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

#define LOG_ENGINE_TRACE(...)				Custom::Log::GetEngineLogger()->Log(Custom::LogMode::trace,			Custom::LogColor::white,		__VA_ARGS__);
#define LOG_ENGINE_INFO(...)				Custom::Log::GetEngineLogger()->Log(Custom::LogMode::info,			Custom::LogColor::green,		__VA_ARGS__);
#define LOG_ENGINE_SUCCESS(...)				Custom::Log::GetEngineLogger()->Log(Custom::LogMode::success,		Custom::LogColor::boldGreen,	__VA_ARGS__);
#define LOG_ENGINE_DEBUG(...)				Custom::Log::GetEngineLogger()->Log(Custom::LogMode::debug,			Custom::LogColor::blue,			__VA_ARGS__);
#define LOG_ENGINE_WARN(...)				Custom::Log::GetEngineLogger()->Log(Custom::LogMode::warn,			Custom::LogColor::yellow,		__VA_ARGS__);
#define LOG_ENGINE_ERROR(...)				Custom::Log::GetEngineLogger()->Log(Custom::LogMode::error,			Custom::LogColor::magenta,		__VA_ARGS__);
#define LOG_ENGINE_FATAL(...)				Custom::Log::GetEngineLogger()->Log(Custom::LogMode::fatal,			Custom::LogColor::red,			__VA_ARGS__);

#define LOG_TRACE(...)						Custom::Log::GetApplicationLogger()->Log(Custom::LogMode::trace,	Custom::LogColor::white,		__VA_ARGS__);
#define LOG_INFO(...)			LOG_MODE	Custom::Log::GetApplicationLogger()->Log(Custom::LogMode::info,		Custom::LogColor::green,		__VA_ARGS__);
#define LOG_SUCCESS(...)					Custom::Log::GetApplicationLogger()->Log(Custom::LogMode::success,	Custom::LogColor::boldGreen,	__VA_ARGS__);
#define LOG_DEBUG(...)						Custom::Log::GetApplicationLogger()->Log(Custom::LogMode::debug,	Custom::LogColor::blue,			__VA_ARGS__);
#define LOG_WARN(...)						Custom::Log::GetApplicationLogger()->Log(Custom::LogMode::warn,		Custom::LogColor::yellow,		__VA_ARGS__);
#define LOG_ERROR(...)						Custom::Log::GetApplicationLogger()->Log(Custom::LogMode::error,	Custom::LogColor::magenta,		__VA_ARGS__);
#define LOG_FATAL(...)						Custom::Log::GetApplicationLogger()->Log(Custom::LogMode::fatal,	Custom::LogColor::red,			__VA_ARGS__);

#define LOG_BREAK							Custom::Log::GetApplicationLogger()->Log();
#pragma once

#include <string>
#include <iostream>
#include <chrono>

#include "../Base.h"

namespace Custom {
	enum class LogMode { trace, info, success, debug, warn, error, fatal };
	enum class LogColor { green, boldGreen, magenta, yellow, red, boldRed, blue, white };

	class Logger {
	public:
		Logger(const std::string& name, const LogColor color) : m_name(name), m_logColor(color) { }

		template <typename... Args>
		void Log(LogMode mode, LogColor color, const Args&... args) {
			std::string message = ConnectArgs(args...);
			std::string defaultColor = GetLogColor(LogColor::white);

			std::string entry = GetTime() + " " + GetLogColor(m_logColor) + m_name + defaultColor + "| " + GetLogColor(color) + GetLogMode(mode) + defaultColor + "| " + defaultColor + message;
			std::cout << entry << std::endl;
		}

	private:
		std::string m_name;
		LogColor m_logColor;

		template <typename T>
		std::string Stringify(const T& val) {
			if constexpr (std::is_convertible_v<T, std::string>) return static_cast<std::string>(val);
			else if constexpr (std::is_arithmetic_v<T>) return std::to_string(val);
			//else if constexpr (std::is_base_of_v<event, T>) return val.ToString();
			else "Unable to stringify message. At CustomEngine/src/Custom/Log/CustomLog.cpp";
		}
		std::string Stringify(const std::string& val) { return val; }

		template <typename... Args>
		std::string ConnectArgs(const Args&... args) { return (Stringify(args) + ...); }

		std::string GetTime() {
			auto currentTime = std::chrono::system_clock::now();
			auto time = std::chrono::system_clock::to_time_t(currentTime);
			std::string timestamp = std::ctime(&time);
			timestamp.pop_back();
			return ("[" + timestamp + "]");
		}
		std::string GetLogColor(LogColor color) {
			switch (color) {
			case LogColor::green:		return "\033[32m";
			case LogColor::boldGreen:	return "\033[1;32m";
			case LogColor::magenta:		return "\033[35m";
			case LogColor::yellow:		return "\033[33m";
			case LogColor::red:			return "\033[31m";
			case LogColor::boldRed:		return "\033[1;31m";
			case LogColor::blue:		return "\033[34m";
			case LogColor::white:		return "\033[37m";
			default:					return "\033[37m";
			}
		}
		std::string GetLogMode(LogMode mode) {
			switch (mode) {
			case LogMode::trace:		return "[TRACE]   ";
			case LogMode::info:			return "[INFO]    ";
			case LogMode::success:		return "[SUCCESS] ";
			case LogMode::debug:		return "[DEBUG]   ";
			case LogMode::warn:			return "[WARNING] ";
			case LogMode::error:		return "[ERROR]   ";
			case LogMode::fatal:		return "[FATAL]   ";
			default:					return "[FAIL]   ";
			}
		}
	};
}
#include <chrono>
#include <string>
#include <iostream>

#include "Custom/Base.h"
#include "LogCode.h"

namespace Custom {
	enum LogMode { trace, info, success, debug, warn, error, fatal };
	enum LogColor { green, boldGreen, magenta, yellow, red, boldRed, blue, white };

	class Logger {
	public:
		Logger(const std::string& name, const LogColor color) : m_name(name), m_logColor(color) { }

		template <typename... Args>
		void Log(LogMode mode, LogColor color, const Args&... args) {
			std::string message = ConnectArgs(args...);

			std::string entry = GetTime() + " " + GetLogColor(m_logColor) + m_name + RESET + "| " + GetLogColor(color) + GetLogMode(mode) + RESET + "| " + RESET + message;
			std::cout << entry << std::endl;
		}

		void Log() {
			std::cout << std::endl;
		}

	private:
		std::string m_name;
		LogColor m_logColor;

		template <typename T>
		std::string Stringify(const T& val) {
			if constexpr (std::is_convertible_v<T, std::string>) return static_cast<std::string>(val);
			else if constexpr (std::is_arithmetic_v<T>) return std::to_string(val);
			else return val.ToString();
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
			case LogColor::green:		return GREEN;
			case LogColor::boldGreen:	return BOLDGREEN;
			case LogColor::magenta:		return MAGENTA;
			case LogColor::yellow:		return YELLOW;
			case LogColor::red:			return RED;
			case LogColor::boldRed:		return BOLDRED;
			case LogColor::blue:		return BLUE;
			case LogColor::white:		return WHITE;
			default:					return BLACK;
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
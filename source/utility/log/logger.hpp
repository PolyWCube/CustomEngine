#ifndef CUSTOM_LOG_LOGGER
#define CUSTOM_LOG_LOGGER

#include <fstream>
#include <iostream>
#include <filesystem>
#include <system_error>
#include "formatter.hpp"

namespace Custom {
	namespace Log {
		template <typename... Args>
		inline constexpr void Program(const Args&... message) {
			std::stringstream os;
			os << FG_BLACK << BG_WHITE << "PROGRAM: " << Custom::Log::getString(message...) << RESET_COLOR;
			std::cout << os.str() << NEW_LINE;
		}

		template <typename... Args>
		inline constexpr void ProgramError(const Args&... message) {
			std::stringstream os;
			os << FG_BLACK << BG_WHITE << "PROGRAM: " << Custom::Log::getString(message...) << RESET_COLOR;
			std::cerr << os.str() << NEW_LINE;
		}

		class Logger {
		public:
			static Logger& getInstance() {
				static Logger instance;
				return instance;
			}

			Logger(const Logger&) = delete;
			Logger& operator=(const Logger&) = delete;
			Logger(Logger&&) = delete;
			Logger& operator=(Logger&&) = delete;

			void setFile(const std::string& directory, const std::string& name, bool createDirectory);

			inline void WRITE(const std::string& message) {
				if (!file.is_open() && !warn) { ProgramError("ERROR log file null"); warn = true; }
				file << message;
				file.flush();
			}
		private:
			Logger() {}

			std::ofstream file;
			bool warn = false;
		};

		void setFile(const std::string& directory, const std::string& name = getFileName(), bool createDirectory = false);
		void setFile(const std::string& directory, bool createDirectory);
	}
}

#endif
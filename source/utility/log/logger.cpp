#include "logger.hpp"

namespace Custom {
	namespace Log {
		Logger::Logger() : run(true) {
			logThead = std::thread(&Logger::Update, this);
		}
		Logger::~Logger() {
			run = false;
			queueCondition.notify_one();
			if (logThead.joinable()) {
				logThead.join();
			}
			if (file.is_open()) {
				file.close();
			}
		}

		void Logger::SetFile(const std::string& directory, const std::string& name, bool createDirectory) {
			if (createDirectory) {
				try {
					std::filesystem::path path(directory);
					if (!std::filesystem::exists(path)) {
						std::filesystem::create_directory(path);
						Program("SUCCESS create log directory : ", directory);
					}
					else Program("WARN log directory already created : ", directory);
				} catch (const std::filesystem::filesystem_error& error) {
					ProgramError("ERROR create log directory : ", error.what(), ' ', error.code());
				} catch (const std::exception& exception) {
					ProgramError("ERROR create log directory : ", exception.what());
				} catch (...) { std::cerr << "ERROR create log directory : unknown" << std::endl; }
			}
			try {
				file.open(directory + name, std::ios::app);
				if (file.is_open()) Program("SUCCESS open log file : ", directory + name);
				else Program("FAIL open log file : ", directory + name);
				warn = false;
			} catch (const std::exception& exception) { ProgramError("ERROR open log file : ", exception.what()); }
		}

		void SetFile(const std::string& directory, const std::string& name, bool createDirectory) {
			Logger::GetInstance().SetFile(directory, name, createDirectory);
		}
		void SetFile(const std::string& directory, bool createDirectory) {
			Logger::GetInstance().SetFile(directory, GetFileName(), createDirectory);
		}
	}
}
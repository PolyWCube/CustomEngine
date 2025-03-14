#include "logger.hpp"

void Custom::Log::Logger::setFile(const std::string& directory, const std::string& name, bool createDirectory) {
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

void Custom::Log::setFile(const std::string& directory, const std::string& name, bool createDirectory) { Logger::getInstance().setFile(directory, name, createDirectory); }
void Custom::Log::setFile(const std::string& directory, bool createDirectory) { Logger::getInstance().setFile(directory, getFileName(), createDirectory); }
#ifndef CUSTOM_LOG_LOGGER
#define CUSTOM_LOG_LOGGER

#include <iostream>
#include <filesystem>
#include <system_error>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include "formatter.hpp"

namespace Custom {
	namespace Log {
		template <typename... Args>
		inline constexpr void Program(const Args&... message) {
			std::stringstream os;
			os << FG_BLACK << BG_WHITE << "PROGRAM: " << Custom::Log::GetString(message...) << RESET_COLOR;
			std::cout << os.str() << NEW_LINE;
		}

		template <typename... Args>
		inline constexpr void ProgramError(const Args&... message) {
			std::stringstream os;
			os << FG_BLACK << BG_WHITE << "PROGRAM: " << Custom::Log::GetString(message...) << RESET_COLOR;
			std::cerr << os.str() << NEW_LINE;
		}

		class Logger {
		public:
			static Logger& GetInstance() {
				static Logger instance;
				return instance;
			}
			~Logger();

			Logger(const Logger&) = delete;
			Logger& operator=(const Logger&) = delete;
			Logger(Logger&&) = delete;
			Logger& operator=(Logger&&) = delete;

			void SetFile(const std::string& directory, const std::string& name, bool createDirectory);

			inline void Update() {
				while (run) {
					std::string message;
					{
						std::unique_lock<std::mutex> lock(queueMutex);
						queueCondition.wait(lock, [this] { return !queue.empty() || !run; });
						if (!run && queue.empty()) {
							return;
						}
						message = queue.front();
						queue.pop();
					}
					if (file.is_open())
					{
						file << message;
						file.flush();
					}
					else if (!warn)
					{
						ProgramError("ERROR log file null");
						warn = true;
					}
				}
			}
			inline void Enqueue(const std::string& message) {
				{
					std::lock_guard<std::mutex> lock(queueMutex);
					queue.push(message);
				}
				queueCondition.notify_one();
			}
		private:
			Logger();

			std::ofstream file;
			bool warn = false;

			std::thread logThead;
			std::queue<std::string> queue;
			std::mutex queueMutex;
			std::condition_variable queueCondition;
			std::atomic<bool> run;
		};

		void SetFile(const std::string& directory, const std::string& name = GetFileName(), bool createDirectory = false);
		void SetFile(const std::string& directory, bool createDirectory);
	}
}

#endif
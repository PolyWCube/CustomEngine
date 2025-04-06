#ifndef CUSTOM_LOG
#define CUSTOM_LOG

#include "logger.hpp"
#include "formatter.hpp"

#define DEFINE_LOG_LEVEL(level, fg_color, bg_color) \
namespace Custom { \
	namespace Log { \
		template <typename... Args> \
		inline constexpr void level(const Args&... message) { \
			std::stringstream os, ofs; \
			std::string timestamp = getTimestamp(); \
			os << fg_color << bg_color << timestamp << #level << ": " << Custom::Log::getString(message...) << RESET_COLOR; \
			ofs << timestamp << #level << ": " << Custom::Log::getString(message...) << "\n"; \
			std::cout << os.str() << NEW_LINE; \
			Logger::getInstance().WRITE(ofs.str()); \
		} \
	} \
}

DEFINE_LOG_LEVEL(Trace, FG_WHITE, NONE);
DEFINE_LOG_LEVEL(Info, FG_GREEN, NONE);
DEFINE_LOG_LEVEL(Success, FG_WHITE, BG_GREEN);
DEFINE_LOG_LEVEL(Warn, FG_YELLOW, NONE);
DEFINE_LOG_LEVEL(Error, FG_RED, NONE);
DEFINE_LOG_LEVEL(Fatal, FG_WHITE, BG_RED);
DEFINE_LOG_LEVEL(Debug, FG_BLUE, NONE);

namespace Custom {
	namespace Log {
		void Initial();
	}
}

#endif
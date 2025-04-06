#ifndef CUSTOM_WIN32_UTILITY
#define CUSTOM_WIN32_UTILITY

namespace Custom {
	namespace Utility {
		inline std::wstring StringToWstring(const std::string& utf8) {
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			return converter.from_bytes(utf8);
		}
	}
}

#endif
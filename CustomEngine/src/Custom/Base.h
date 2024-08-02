#pragma once

#ifdef CUSTOM_PLATFORM_WINDOWS
#else
	#error Custom only support Windows!
#endif

#ifdef CUSTOM_ENABLE_FAST_LOG
	#define LOG_FAST_MODE true
#else 
	#define LOG_FAST_MODE false
#endif

#define LOG_MODE if (!LOG_FAST_MODE)

#ifdef CUSTOM_ENABLE_ASSERT
	#define LOG_ASSERT(x, ...) { if (!(x)) LOG_ERROR("Assertion failed : ", __VA_ARGS__) __debugbreak(); }
	#define LOG_ENGINE_ASSERT(x, ...) { if (!(x)) LOG_ENGINE_ERROR("Assertion failed : ", __VA_ARGS__) __debugbreak(); }
#else
	#define LOG_ASSERT(x, ...)
	#define LOG_ENGINE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#ifndef CUSTOM_BASE
#define CUSTOM_BASE

#ifdef CUSTOM_PLATFORM_WINDOWS
#else 
	#error Custom Engine only support Windows
#endif

#ifdef CUSTOM_ALL_LOG
	#define CUSTOM_WINDOW_FULL_LOG
#endif

#define BIT(x) (1 << x)
#endif
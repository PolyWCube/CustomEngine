#ifndef CUSTOM_WINDOW_EVENT
#define CUSTOM_WINDOW_EVENT

#include "utility/event.hpp"
#include "utility/math/vector.hpp"

namespace Custom {
	namespace Event {
		class WindowResize : public Event {
		public :
			WindowResize(Math::Vector2<uint16_t> size) : size(size) {}

			inline uint16_t getWidth() const { return size.x; }
			inline uint16_t getHeight() const { return size.y; }
			inline Math::Vector2<uint16_t> getSize() const { return size; }

			std::string getStream() const override {
				std::ostringstream oss;
				oss << "Window Resize: " << size;
				return oss.str();
			}

			DEFINE_EVENT_SOURCE(window)
			DEFINE_EVENT_ACTION(resize)
		private :
			Math::Vector2<uint16_t> size;
		};

		class WindowClose : public Event {
		public :
			WindowClose() {}

			std::string getStream() const override {
				return "Window Close";
			}

			DEFINE_EVENT_SOURCE(window)
			DEFINE_EVENT_ACTION(close)
		};
	}
}

#endif
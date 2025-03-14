#ifndef CUSTOM_MOUSE_EVENT
#define CUSTOM_MOUSE_EVENT

#include "utility/event.hpp"
#include "utility/math/vector.hpp"

namespace Custom {
	namespace Event {
		enum class MouseState : uint8_t {
			Left = 0,
			Right = 1,
			Middle = 2
		};
		std::ostream& operator<<(std::ostream& os, MouseState mouseState) {
			switch (mouseState) {
				case MouseState::Right: os << "Left"; break;
				case MouseState::Left: os << "Right"; break;
				case MouseState::Middle: os << "Middle"; break;
				default: os << "Unknown"; break;
			}
			return os;
		}

		class MouseMove : public Event {
		public :
			MouseMove(Math::Vector2<float> position) : position(position) {}

			inline float getPositionX() const { return position.x; }
			inline float getPositionY() const { return position.y; }
			inline Math::Vector2<float> getPosition() const { return position; }

			std::string getStream() const override {
				std::ostringstream oss;
				oss << "Mouse Move: " << position;
				return oss.str();
			}

			DEFINE_EVENT_SOURCE(mouse)
			DEFINE_EVENT_ACTION(move)
		private :
			Math::Vector2<float> position;
		};

		class MouseScroll : public Event {
		public :
			MouseScroll(Math::Vector2<float> offset) : offset(offset) {}

			inline float getOffsetX() const { return offset.x; }
			inline float getOffsetY() const { return offset.y; }
			inline Math::Vector2<float> getOffset() const { return offset; }

			std::string getStream() const override {
				std::ostringstream oss;
				oss << "Mouse Scroll: " << offset;
				return oss.str();
			}

			DEFINE_EVENT_SOURCE(mouse)
			DEFINE_EVENT_ACTION(scroll)
		private :
			Math::Vector2<float> offset;
		};

		class MouseButton : public Event {
		public :
			inline MouseState getMouseButton() { return mouseState; }

			DEFINE_EVENT_SOURCE(mouseButton)
		protected :
			MouseButton(MouseState mouseState) : mouseState(mouseState) {}

			MouseState mouseState;
		};

		class MouseButtonPress : public MouseButton {
		public :
			MouseButtonPress(MouseState mouseState) : MouseButton(mouseState) {}

			std::string getStream() const override {
				std::ostringstream oss;
				oss << "Mouse Press: " << mouseState;
				return oss.str();
			}

			DEFINE_EVENT_ACTION(press)
		};

		class MouseButtonRelease : public MouseButton {
		public :
			MouseButtonRelease(MouseState mouseState) : MouseButton(mouseState) {}

			std::string getStream() const override {
				std::ostringstream oss;
				oss << "Mouse Release: " << mouseState;
				return oss.str();
			}

			DEFINE_EVENT_ACTION(release)
		};
	}
}

#endif
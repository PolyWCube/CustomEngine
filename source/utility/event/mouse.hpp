#ifndef CUSTOM_MOUSE_EVENT
#define CUSTOM_MOUSE_EVENT

#include "event.hpp"
#include "utility/math/vector.hpp"

namespace Custom {
	namespace Event {
		enum class MouseState : uint8_t {
			Left = 0,
			Right = 1,
			Middle = 2
		};
		static std::ostream& operator<<(std::ostream& os, MouseState mouseState) {
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
			MouseMove(const Math::Vector2<float>& position) : position(position) {}

			inline float GetPositionX() const { return position.x; }
			inline float GetPositionY() const { return position.y; }
			inline Math::Vector2<float> GetPosition() const { return position; }

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
			MouseScroll(const Math::Vector2<float>& offset) : offset(offset) {}

			inline float GetOffsetX() const { return offset.x; }
			inline float GetOffsetY() const { return offset.y; }
			inline Math::Vector2<float> GetOffset() const { return offset; }

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

			inline float GetPositionX() const { return position.x; }
			inline float GetPositionY() const { return position.y; }
			inline Math::Vector2<float> GetPosition() const { return position; }

			DEFINE_EVENT_SOURCE(mouseButton)
		protected :
			MouseButton(MouseState mouseState, Math::Vector2<float> position) : mouseState(mouseState), position(position) {}

			MouseState mouseState;
			Math::Vector2<float> position;
		};

		class MouseButtonPress : public MouseButton {
		public :
			MouseButtonPress(MouseState mouseState, Math::Vector2<float> position) : MouseButton(mouseState, position) {}

			std::string getStream() const override {
				std::ostringstream oss;
				oss << "Mouse Press: " << mouseState << " in " << position;
				return oss.str();
			}

			DEFINE_EVENT_ACTION(press)
		};

		class MouseButtonRelease : public MouseButton {
		public :
			MouseButtonRelease(MouseState mouseState, Math::Vector2<float> position) : MouseButton(mouseState, position) {}

			std::string getStream() const override {
				std::ostringstream oss;
				oss << "Mouse Release: " << mouseState << " in " << position;
				return oss.str();
			}

			DEFINE_EVENT_ACTION(release)
		};
	}
}

#endif
#pragma once

#include "Event.h"

namespace Custom {
	class MouseEvent : public Event { public : EVENT_CATEGORY(input | mouse) };

	class MouseMoveEvent : public MouseEvent {
	public:
		MouseMoveEvent(float xPostion, float yPosition) : xPosition(xPostion), yPosition(yPosition) { }

		inline float GetXPosition() const { return xPosition; }
		inline float GetYPosition() const { return yPosition; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse move : " << xPosition << ", " << yPosition;
			return ss.str();
		}

		EVENT_TYPE(mouseMove)
	private :
		float xPosition, yPosition;
	};

	class MouseButtonEvent : public MouseEvent {
	public:
		inline int GetButton() const { return button; }
	protected :
		MouseButtonEvent(int button) : button(button) { }

		int button;
	};
	class MouseButtonPressEvent : public MouseButtonEvent {
	public:
		MouseButtonPressEvent(int button) : MouseButtonEvent(button) { }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse button press : " << button;
			return ss.str();
		}

		EVENT_TYPE(mouseButtonPress)
	};
	class MouseButtonReleaseEvent : public MouseButtonEvent {
	public:
		MouseButtonReleaseEvent(int button) : MouseButtonEvent(button) { }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse button release : " << button;
			return ss.str();
		}

		EVENT_TYPE(mouseButtonRelease)
	};

	class MouseScrollEvent : public MouseEvent {
	public:
		MouseScrollEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) { }

		inline float GetXOffset() const { return xOffset; }
		inline float GetYOffset() const { return yOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse scroll : " << xOffset << ", " << yOffset;
			return ss.str();
		}

		EVENT_TYPE(mouseScroll)
	private:
		float xOffset, yOffset;
	};
}
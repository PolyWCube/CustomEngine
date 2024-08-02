#pragma once

#include "Event.h"

namespace Custom {
	class KeyEvent : public Event {
	public :
		inline int GetKeyCode() const { return keycode; }

		EVENT_CATEGORY(input | keyboard)
	protected :
		KeyEvent(int keycode) : keycode(keycode) { }

		int keycode;
	};

	class KeyPressEvent : public KeyEvent {
	public :
		KeyPressEvent(int keycode, int repeatCount) : KeyEvent(keycode), repeatCount(repeatCount) { }
		
		inline int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key press : " << keycode << " [" << repeatCount << "repeats]";
			return ss.str();
		}

		EVENT_TYPE(keyPress)
	private :
		int repeatCount;
	};

	class KeyReleaseEvent : public KeyEvent {
	public:
		KeyReleaseEvent(int keycode) : KeyEvent(keycode) { }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key press : " << keycode;
			return ss.str();
		}

		EVENT_TYPE(keyRelease)
	};
}
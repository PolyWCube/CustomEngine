#pragma once

#include "Event.h"

namespace Custom {
	class ApplicationEvent : public Event { public : EVENT_CATEGORY(application) };

	class WindowResizeEvent : public ApplicationEvent {
	public :
		WindowResizeEvent(unsigned int width, unsigned int height) : width(width), height(height) {}

		inline unsigned int GetWidth() const { return width; }
		inline unsigned int GetHeight() const { return height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Window resize :" << width << ", " << height;
			return ss.str();
		}

		EVENT_TYPE(windowResize)
	private :
		unsigned int width, height;
	};
	
	class WindowCloseEvent : public ApplicationEvent {
	public :
		WindowCloseEvent() {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Window close";
			return ss.str();
		}

		EVENT_TYPE(windowClose)
	};

	class ApplicationTickEvent : public ApplicationEvent {
	public:
		ApplicationTickEvent() {}

		EVENT_TYPE(applicationTick)
	};
	class ApplicationRenderEvent : public ApplicationEvent {
	public:
		ApplicationRenderEvent() {}

		EVENT_TYPE(applicationRender)
	};
	class ApplicationUpdateEvent : public ApplicationEvent {
	public:
		ApplicationUpdateEvent() {}

		EVENT_TYPE(applicationUpdate)
	};
}
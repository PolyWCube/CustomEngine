#pragma once

#include "CustomPrecompileHeader.h"

#include "Custom/Base.h"

namespace Custom {
	enum class EventType {
		none = 0,
		windowClose, windowResize, windowFocus, windowDefocus, windowMove,
		applicationUpdate, applicationRender, applicationTick,
		keyPress, keyRelease,
		mouseButtonPress, mouseButtonRelease, mouseMove, mouseScroll
	};
	enum EventCategory {
		none = 0,
		application		= BIT(0),
		input			= BIT(1),
		keyboard		= BIT(2),
		mouse			= BIT(3),
		mouseButton		= BIT(4)
	};

#define EVENT_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
						 virtual EventType GetType() const override { return GetStaticType(); }\
						 virtual const char* GetName() const override { return #type; }
#define EVENT_CATEGORY(category) virtual int GetCategory() const override { return category; }

	class Event {
		friend class EventDispatch;
	public :
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategory() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool FromCategory(EventCategory category) { return GetCategory() & category; }
		bool handle = false;
	};

	class EventDispatch {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public :
		EventDispatch(Event& event) : event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> function) {
			if (event.GetType() == T::GetStaticType()) {
				event.handle = function(*(T*)&event);
				return true;
			}
			return false;
		}
	private :
		Event& event;
	};
}
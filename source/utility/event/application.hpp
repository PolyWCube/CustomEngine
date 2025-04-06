#ifndef CUSTOM_APPLICATION_EVENT
#define CUSTOM_APPLICATION_EVENT

#include "event.hpp"
#include "utility/math/vector.hpp"

namespace Custom {
	namespace Event {
		class ApplicationTick : public Event {
		public :
			ApplicationTick() {}

			std::string getStream() const override {
				return "Application Tick";
			}

			DEFINE_EVENT_SOURCE(application)
			DEFINE_EVENT_ACTION(tick)
		};

		class ApplicationUpdate : public Event {
		public :
			ApplicationUpdate() {}

			std::string getStream() const override {
				return "Application Update";
			}

			DEFINE_EVENT_SOURCE(application)
			DEFINE_EVENT_ACTION(update)
		};

		class ApplicationRender : public Event {
		public :
			ApplicationRender() {}

			std::string getStream() const override {
				return "Application Render";
			}

			DEFINE_EVENT_SOURCE(application)
			DEFINE_EVENT_ACTION(render)
		};
	}
}

#endif
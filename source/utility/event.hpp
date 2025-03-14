#ifndef CUSTOM_EVENT
#define CUSTOM_EVENT

#include "precompiledheader.hpp"
#include "base.hpp"

namespace Custom {
	namespace Event {
		#define DEFINE_EVENT_SOURCE(source) \
			static Source getStaticSource() { return Source::source; } \
			virtual Source getSource() const override { return getStaticSource(); } \
			virtual uint8_t getSourceFlag() const override { return static_cast<uint8_t>(Source::source); }
		#define DEFINE_EVENT_ACTION(action) \
			static Action getStaticAction() { return Action::action; } \
			virtual Action getAction() const override { return getStaticAction(); } \
			virtual uint16_t getActionFlag() const override { return static_cast<uint16_t>(Action::action); }

		enum class Source : uint8_t {
			none = 0,
			application = BIT(0),
			window = BIT(1),
			keyboard = BIT(2),
			mouse = BIT(3),
			mouseButton = BIT(4)
		};

		enum class Action : uint16_t {
			none = 0,
			close = BIT(0),
			press = BIT(1),
			release = BIT(2),
			move = BIT(3),
			focus = BIT(4),
			blur = BIT(5),
			scroll = BIT(6),
			update = BIT(7),
			render = BIT(8),
			tick = BIT(9),
			resize = BIT(10)
		};

		class Event {
			friend class Manager;
		public :
			virtual Source getSource() const = 0;
			virtual Action getAction() const = 0;
			virtual std::string getStream() const = 0;
			virtual uint8_t getSourceFlag() const = 0;
			virtual uint16_t getActionFlag() const = 0;

			inline bool isFrom(Source source) { return getSourceFlag() & static_cast<uint8_t>(source); }
			inline bool is(Action action) { return getActionFlag() & static_cast<uint16_t>(action); }

			friend std::ostream& operator<<(std::ostream& os, const Custom::Event::Event& event) {
				return os << event.getStream();
			}
		protected :
			bool handle = false;
		};

		class Manager {
			template<typename T>
			using EventFunction = std::function<bool(T&)>;
		public :
			Manager(Event& event) : event(event) {}

			template<typename T>
			bool Dispatch(EventFunction<T> function) {
				if (event.getSource() == T::getStaticSource() && event.getAction() == T::getStaticAction()) {
					event.handle = function(*(T*)&event);
					return true;
				}
				return false;
			}
		private :
			Event& event;
		};
	}
}

#endif
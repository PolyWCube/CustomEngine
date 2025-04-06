#ifndef CUSTOM_LAYER
#define CUSTOM_LAYER

#include "utility/event/event.hpp"

namespace Custom {
	namespace Layer {
		class Layer {
		public :
			Layer(const std::string& name);
			virtual ~Layer();

			virtual void Attach() {}
			virtual void Detach() {}
			virtual void Update() {}
			virtual void Event(Event::Event& event) {}
		protected :
			std::string name;
		};
	}
}

#endif
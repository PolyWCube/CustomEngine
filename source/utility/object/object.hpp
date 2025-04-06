#ifndef CUSTOM_OBJECT
#define CUSTOM_OBJECT

#include "precompiled_header.hpp"

namespace Custom {
	namespace Object {
		using ID = uint32_t;

		class Object {
		public :
			Object(ID id) : id(id) {}

			ID getID() const { return id; }
		private :
			ID id;
		};
	}
}

#endif
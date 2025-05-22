#include "manager.hpp"

namespace Custom {
	namespace Object {
		Object::Object() {
			id = Manager::GetInstance().CreateObject(std::unique_ptr<Object>(this));
		}
		Object::~Object() {
			Manager::GetInstance().DestroyObject(id);
		}
	}
}
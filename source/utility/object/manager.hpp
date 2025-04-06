#ifndef CUSTOM_OBJECT_MANAGER
#define CUSTOM_OBJECT_MANAGER

#include "property.hpp"
#include "object.hpp"

namespace Custom {
	namespace Object {
		class Manager {
		public :
			ID CreateObject() {
				ID newID = nextID++;
				objects.emplace(newID, Object(newID));
				return newID;
			}
			void DestroyObject(ID id) {
				objects.erase(id);
				properties.erase(id);
			}

			template <typename T>
			void AddProperty(ID id) {
				properties[id][typeid(T)] = std::make_unique<T>();
			}
			template <typename T>
			T* GetProperty(ID id) {
				std::type_index type = typeid(T);
				if (properties.find(id) != properties.end() && properties[id].find(type) != properties[id].end()) return dynamic_cast<T*>(properties[id][type].get());;
				return nullptr;
			}
		private :
			std::unordered_map<ID, Object> objects;
			std::unordered_map<ID, std::unordered_map<std::type_index, std::unique_ptr<Property>>> properties;
			ID nextID = 0;
		};
	}
}

#endif
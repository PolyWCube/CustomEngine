#ifndef CUSTOM_OBJECT_MANAGER
#define CUSTOM_OBJECT_MANAGER

#include "precompiled_header.hpp"
#include "property/window.hpp"
#include "property/renderer.hpp"

namespace Custom {
	namespace Object {
		template <typename D, typename ID, typename P>
		class ManagerBase {
		public :
			template <typename T>
			void AddProperty(ID id) { static_cast<D*>(this)->template AddPropertyImplement<T>(id); }

			template <typename T>
			T* GetProperty(ID id) { return static_cast<D*>(this)->template GetPropertyImplement<T>(id); }
		};
		using ID = uint32_t;
		class Object;
		class Manager : public ManagerBase<Manager, ID, Property>  {
		public :
			static Manager& GetInstance() {
				static Manager instance;
				return instance;
			}

			inline ID CreateObject(std::unique_ptr<Object> object) {
				ID newID = nextID++;
				objects.emplace(newID, std::move(object));
				return newID;
			}
			inline void DestroyObject(ID id) {
				objects.erase(id);
				properties.erase(id);
			}

			template <typename T>
			inline void AddPropertyImplement(ID id) {
				properties[id][typeid(T)] = std::make_unique<T>();
			}
			template <typename T>
			inline T* GetPropertyImplement(ID id) {
				std::type_index type = typeid(T);
				if (properties.find(id) != properties.end() && properties[id].find(type) != properties[id].end()) return static_cast<T*>(properties[id][type].get());;
				return nullptr;
			}
		private :
			Manager() = default;
			Manager(const Manager&) = delete;
			Manager& operator=(const Manager&) = delete;

			std::unordered_map<ID, std::unique_ptr<Object>> objects;
			std::unordered_map<ID, std::unordered_map<std::type_index, std::unique_ptr<Property>>> properties;
			ID nextID = 0;
		};

		class Object {
		public :
			Object(ID id) : id(id) {}
			Object();
			~Object();

			template <typename T>
			inline void AddProperty() {
				Manager::GetInstance().template AddProperty<T>(id);
			}
			template <typename T>
			inline T* GetProperty() {
				return Manager::GetInstance().template GetProperty<T>(id);
			}

			ID GetID() const { return id; }
		private :
			ID id;
		};
	}
}

#endif
#ifndef CUSTOM_LAYERSTACK
#define CUSTOM_LAYERSTACK

#include "layer.hpp"

#include <vector>

namespace Custom {
	namespace Layer {
		class Manager {
		public :
			Manager();
			~Manager();

			void AddLayer(Layer* layer);
			void AddOverlay(Layer* overlay);
			void RemoveLayer(Layer* layer);
			void RemoveOverlay(Layer* overlay);

			std::vector<Layer*>::iterator begin() { return layers.begin(); }
			std::vector<Layer*>::iterator end() { return layers.end(); }
		private :
			std::vector<Layer*> layers;
			std::vector<Layer*>::iterator insertPoint;
		};
	}
}

#endif
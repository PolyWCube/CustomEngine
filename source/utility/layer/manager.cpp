#include "precompiled_header.hpp"
#include "manager.hpp"

namespace Custom {
	namespace Layer {
		Manager::Manager() {
			insertPoint = layers.begin();
		}
		Manager::~Manager() {
			for (Layer* layer : layers) delete layer;
		}

		void Manager::AddLayer(Layer* layer) {
			insertPoint = layers.emplace(insertPoint, layer);
		}
		void Manager::AddOverlay(Layer* overlay) {
			layers.emplace_back(overlay);
		}
		void Manager::RemoveLayer(Layer* layer) {
			auto deletePoint = std::find(layers.begin(), layers.end(), layer);
			if (deletePoint != layers.end()) {
				layers.erase(deletePoint);
				insertPoint--;
			}
		}
		void Manager::RemoveOverlay(Layer* overlay) {
			auto deletePoint = std::find(layers.begin(), layers.end(), overlay);
			if (deletePoint != layers.end()) {
				layers.erase(deletePoint);
			}
		}
	}
}
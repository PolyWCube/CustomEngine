#include "CustomPrecompileHeader.h"
#include "LayerStack.h"

namespace Custom {
	LayerStack::LayerStack() {
		insertIndex = 0;
	}
	LayerStack::~LayerStack() {
		for (Layer* layer : stack) delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		stack.emplace(stack.begin() + insertIndex, layer);
		insertIndex++;
	}
	void LayerStack::PushOverlay(Layer* overlay) {
		stack.emplace_back(overlay);
	}
	void LayerStack::PopLayer(Layer* layer) {
		std::vector<Layer*>::iterator iterator = std::find(stack.begin(), stack.end(), layer);
		if (iterator != stack.end()) {
			stack.erase(iterator);
			insertIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay) {
		std::vector<Layer*>::iterator iterator = std::find(stack.begin(), stack.end(), overlay);
		if (iterator != stack.end()) {
			stack.erase(iterator);
		}
	}
}
#pragma once

#include "Custom/Base.h"
#include "Layer.h"

namespace Custom {
	class LayerStack {
	public :
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return stack.begin(); }
		std::vector<Layer*>::iterator end() { return stack.end(); }
	private :
		std::vector<Layer*> stack;
		int insertIndex = 0;
	};
}
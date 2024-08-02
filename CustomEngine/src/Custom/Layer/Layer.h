#pragma once

#include "Custom/Base.h"
#include "Custom/Event/Event.h"

namespace Custom {
	class Layer {
	public :
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return debugName; }
	protected :
		std::string debugName;
	};
}


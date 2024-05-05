#pragma once

#include <vector>

#include "layer.h"

namespace Elysium
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void Push(Layer* layer);
		void PushOverlay(Layer* overlay);
		void Pop(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::const_iterator cbegin() const { return m_Layers.cbegin(); }
		std::vector<Layer*>::const_iterator cend() const { return m_Layers.cend(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }
		std::vector<Layer*>::const_reverse_iterator rcbegin() const { return m_Layers.crbegin(); }
		std::vector<Layer*>::const_reverse_iterator rcend() const { return m_Layers.crend(); }

	private:
		std::vector<Layer*> m_Layers;
		uint32_t m_LayerIndex = 0;
	};
}
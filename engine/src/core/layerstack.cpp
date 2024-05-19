#include "layer.h"
#include "layerstack.h"

namespace Elysium
{
	LayerStack::~LayerStack()
	{
		for (auto layer : m_Layers)
		{
			delete layer;
		}
	}

	void LayerStack::Push(Layer* layer)
	{
		m_Layers.insert(m_Layers.begin() + m_LayerIndex, layer);
		m_LayerIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.push_back(overlay);
	}

	void LayerStack::Pop(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}
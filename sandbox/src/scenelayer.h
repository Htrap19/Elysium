#pragma once

#include "engine.h"

#include "scenehierarchicalpanel.h"

#include <imgui.h>

class SceneLayer : public Elysium::Layer
{
public:
	SceneLayer()
	{
		m_Scene = Elysium::MakeShared<Elysium::Scene>();
	}

	virtual void OnUpdate(Elysium::Timestep ts) override
	{
		Elysium::RenderCommand::Clear();
		m_Scene->OnUpdate(ts);
	}

protected:
	Elysium::Shared<Elysium::Scene> m_Scene;
};
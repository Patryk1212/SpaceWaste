#include "pch.h"
#include "UILayer.h"

void UILayer::onAttach()
{
}

void UILayer::onUpdate(float deltaTime)
{
	bool show_demo_window = true;
	ImGui::ShowDemoWindow(&show_demo_window);
}

void UILayer::onRender()
{
}

bool UILayer::onEvent(Engine::Event& event)
{
	return false;
}

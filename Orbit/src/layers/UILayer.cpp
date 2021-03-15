#include "pch.h"
#include "UILayer.h"

void UILayer::onAttach()
{
	std::cout << "UI Layer Attached" << std::endl;
}

void UILayer::onUpdate(float deltaTime)
{
	bool show_demo_window = true;
	ImGui::ShowDemoWindow(&show_demo_window);
}

void UILayer::onRender()
{
}

void UILayer::passCamera(std::unique_ptr<Engine::CameraController>& cc)
{
}

bool UILayer::onEvent(Engine::Event& event)
{
	return false;
}

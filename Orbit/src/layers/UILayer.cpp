#include "pch.h"
#include "UILayer.h"

void UILayer::onAttach()
{
	std::cout << "UI Layer Attached" << std::endl;

	initSlider();
	initControls();
	initGeneralInfo();
	initObjectList();
	initMenu();
}

void UILayer::onUpdate(float deltaTime)
{
	bool show_demo_window = true;
	ImGui::ShowDemoWindow(&show_demo_window);
	
	for (const auto& window : uiWindows)
	{
		window->onUpdate();
	}

	for (const auto& window : uiWindows)
	{
		if (window->getType() == UIType::BUTTON_LIST)
		{
			for (auto& button : window->getButtons())
			{
				for (const auto& windows : uiWindows)
				{
					// dont check for none
					if (windows->getInstanceType() != UIWindowInstance::NONE && button.change && windows->getInstanceType() == button.type)
					{
						button.change = false;
						windows->show(button.clicked);
						break;
					}
				}
			}
		}
	}
}

bool UILayer::onEvent(Engine::Event& event)
{
	//Engine::MouseButtonPressedEvent& e = (Engine::MouseButtonPressedEvent&)event;
	//
	//if (e.getEventType() == Engine::EventType::MOUSE_PRESSED)
	//{
	//	for (const auto& window : uiWindows)
	//	{
	//		if (window->getType() == UIType::BUTTON_LIST)
	//		{
	//			for (auto& button : window->getButtons())
	//			{
	//				for (const auto& windows : uiWindows)
	//				{
	//					// dont check for none
	//					if (windows->getInstanceType() != UIWindowInstance::NONE && button.change && windows->getInstanceType() == button.type)
	//					{
	//						std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
	//						std::cout << (int)windows->getInstanceType() << std::endl;
	//						std::cout << (int)button.type << std::endl;
	//						std::cout << button.clicked << std::endl;
	//						
	//						button.change = false;
	//						windows->show(button.clicked);
	//						break;
	//						//if (button.clicked) return true;
	//					}
	//				}
	//			}
	//
	//			return false;
	//		}
	//	}
	//}

	return false;
}

void UILayer::initSlider()
{
	ImVec2 pos{ 10.f, 10.f };
	ImVec2 size{ 400.f, 50.f };
	UIWindowSpec spec(UIWindowInstance::TIME_LINE, "Time line", pos, size, 0.5f, false, true, true, true);

	std::unique_ptr<SingleUIWindow> slider = std::make_unique<UISlider>(spec, "Time line", 0.f, 24.f);

	uiWindows.emplace_back(std::move(slider));
}

void UILayer::initControls()
{
	ImVec2 pos{ 500.f, 500.f };
	ImVec2 size{ 170.f, 100.f };
	UIWindowSpec spec(UIWindowInstance::CONTROLS, "controls", pos, size, 0.5f, false, true, true, true);

	std::vector<std::string> text;
	text.emplace_back("Move around: ");
	text.emplace_back("Mouse + RMB");
	text.emplace_back("Zoom in/out: ");
	text.emplace_back("Scroll Wheel");

	std::unique_ptr<SingleUIWindow> controls = std::make_unique<UIStandard>(spec, text);

	uiWindows.emplace_back(std::move(controls));
}

void UILayer::initGeneralInfo()
{
	ImVec2 pos{ 500.f, 800.f };
	ImVec2 size{ 200.f, 50.f };
	UIWindowSpec spec(UIWindowInstance::GENERAL_INFO, "info", pos, size, 0.5f, false, true, true, true);

	std::vector<std::string> text;
	text.emplace_back("Space Object in Total: ");
	text.emplace_back("");

	std::unique_ptr<SingleUIWindow> info = std::make_unique<UIStandard>(spec, text);

	uiWindows.emplace_back(std::move(info));
}

void UILayer::initObjectList()
{
}

void UILayer::initMenu()
{
	ImVec2 pos{ 1160.f, 30.f };
	ImVec2 size{ 100.f, 180.f };
	UIWindowSpec spec(UIWindowInstance::NONE, "menu", pos, size, 0.f, false, true, true, true);

	std::vector<UIButton> buttons;
	buttons.emplace_back(UIButton(UIWindowInstance::NONE, "EXIT", { 1.f, .1f, .0f, 1.f }, { 0.f, .5f, .9f, 1.f }, { 0.f, .0f, .9f, 1.f }));
	buttons.emplace_back(UIButton(UIWindowInstance::GENERAL_INFO, "INFO", { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }));
	buttons.emplace_back(UIButton(UIWindowInstance::OBJECTS_LIST, "LIST", { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }));
	buttons.emplace_back(UIButton(UIWindowInstance::TIME_LINE, "TIME LINE", { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }));
	buttons.emplace_back(UIButton(UIWindowInstance::CONTROLS, "CONTROLS", { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }));

	std::unique_ptr<SingleUIWindow> info = std::make_unique<UIButtonList>(spec, buttons);

	uiWindows.emplace_back(std::move(info));
}

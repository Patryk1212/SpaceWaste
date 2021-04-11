#include "pch.h"
#include "UILayer.h"

void UILayer::onAttach()
{
	std::cout << "UI Layer Attached" << std::endl;

	initImGuiSettings();

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
	
	initImGuiSettings();

	for (const auto& window : uiWindows)
	{
		window->onUpdate();

		if (window->getType() == UIType::BUTTON_LIST)
		{
			for (auto& button : window->getButtons())
			{
				for (const auto& windows : uiWindows)
				{
					if (windows->getInstanceType() != UIWindowInstance::EXIT && button.change && windows->getInstanceType() == button.type)
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
	Engine::MouseButtonPressedEvent& e = (Engine::MouseButtonPressedEvent&)event;
	
	for (const auto& window : uiWindows)
	{
		if (window->getType() == UIType::BUTTON_LIST)
		{
			for (auto& button : window->getButtons())
			{
				for (const auto& windows : uiWindows)
				{
					if (windows->getInstanceType() == UIWindowInstance::EXIT && button.change && windows->getInstanceType() == button.type)
					{
						// exit button pressed
						return false;
					}
				}
			}
		}
	}

	return true;
}

void UILayer::initImGuiSettings()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->FrameRounding = 8.f;
	style->GrabRounding = 8.f;
		 
	style->ItemSpacing.x = 6.f;
	style->ItemSpacing.y = 7.f;
		 
	style->WindowBorderSize = 0.f;
	style->WindowRounding = 8.f;
	style->WindowTitleAlign.x = 0.5f;
	style->WindowTitleAlign.y = 0.5f;
		 
	style->WindowMenuButtonPosition = 1;

	/* text */
	ImVec4 color{ 0.82f, 0.82f, 0.82f, 255 };
	style->Colors[0] = color;

	/* window bg */
	color = { 0.03f, 0.03f, 0.03f, 255 };
	style->Colors[2] = color;

	/* title bg */
	color = { 0.03f, 0.03f, 0.03f, 255 };
	style->Colors[10] = color;

	/* title bg active */
	color = { 0.03f, 0.03f, 0.03f, 255 };
	style->Colors[11] = color;

	/* slider grab */
	color = { 0.0f, 0.48f, 0.74f, 255 };
	style->Colors[19] = color;

	/* slider active */
	color = { 0.65f, 0.75f, 0.02f, 255 };
	style->Colors[20] = color;
}

void UILayer::initSlider()
{
	ImVec2 pos{ 362.5f, 680.f };
	ImVec2 size{ 555.f, 35.f };
	UIWindowSpec spec(UIWindowInstance::TIME_LINE, "Time line", pos, size, 0.5f, false, true, true, true);

	ImVec4 color_base{ 1.f, .1f, .0f, 1.f };
	ImVec4 color_highlight{ 0.3f, .9f, .2f, 1.f };
	ImVec4 color_active{ .0f, .5f, 1.f, 1.f };
	std::unique_ptr<UIButton> button = std::make_unique<UIButton>("STOP", "PLAY", color_base, color_highlight, color_active);

	std::unique_ptr<SingleUIWindow> slider = std::make_unique<UISlider>(spec, "Visualization Speed", 0.f, 24.f, button);

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
	UIWindowSpec spec(UIWindowInstance::EXIT, "PANEL", pos, size, 0.f, true, true, false, false);

	std::vector<UIButton> buttons;
	buttons.emplace_back(UIButton(UIWindowInstance::EXIT, "EXIT", { 1.f, .1f, .0f, 1.f }, { 0.f, .5f, .9f, 1.f }, { 0.f, .0f, .9f, 1.f }));
	buttons.emplace_back(UIButton(UIWindowInstance::GENERAL_INFO, "INFO", { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }));
	buttons.emplace_back(UIButton(UIWindowInstance::OBJECTS_LIST, "LIST", { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }));
	buttons.emplace_back(UIButton(UIWindowInstance::TIME_LINE, "TIME LINE", { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }));
	buttons.emplace_back(UIButton(UIWindowInstance::CONTROLS, "CONTROLS", { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }, { 0.f, .5f, .9f, 1.f }));

	std::unique_ptr<SingleUIWindow> info = std::make_unique<UIButtonList>(spec, buttons);

	uiWindows.emplace_back(std::move(info));
}

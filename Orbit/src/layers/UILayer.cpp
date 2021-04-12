#include "pch.h"
#include "UILayer.h"

void UILayer::onAttach()
{
	std::cout << "UI Layer Attached" << std::endl;

	initImGuiSettings();

	initSlider();
	initControls();
	
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
		else if (window->getType() == UIType::SLIDER)
		{
			Engine::Message message;
			message.status.push_back(window->isButtonClicked());
			message.intNumber.push_back(window->getValue());
			mainLayerHandle->receiveMessage(message);
		}
	}
	
	return true;
}

void UILayer::setObserver(std::shared_ptr<Layer>& observer)
{
	mainLayerHandle = observer;
}

void UILayer::receiveMessage(const Engine::Message& message)
{
	initGeneralInfo(message.intNumber[0]);
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

	/* slider */
	color = { 0.f, 0.f, 0.f, 255 };
	style->Colors[7] = color;

	color = { 0.f, 0.03f, 0.18f, 255 };
	style->Colors[8] = color;

	color = { 0.21f, 0.1f, 0.f, 255 };
	style->Colors[9] = color;

	/* title bg */
	color = { 0.03f, 0.03f, 0.03f, 255 };
	style->Colors[10] = color;
	style->Colors[11] = color;
	style->Colors[12] = color;

	/* slider grab */
	color = { .1f, .2f, .8f, 255 };
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
	ImVec4 color_highlight{ .1f, .2f, .8f, 1.f };
	ImVec4 color_active{ .1f, .2f, 1.f, 1.f };
	std::unique_ptr<UIButton> button = std::make_unique<UIButton>("STOP", "PLAY", color_base, color_highlight, color_active);

	std::unique_ptr<SingleUIWindow> slider = std::make_unique<UISlider>(spec, "Visualization Speed", 1, 5, button);

	uiWindows.emplace_back(std::move(slider));
}

void UILayer::initControls()
{
	ImVec2 pos{ 10.f, 640.f };
	ImVec2 size{ 216.f, 70.f };
	UIWindowSpec spec(UIWindowInstance::CONTROLS, "controls", pos, size, 0.5f, false, true, true, true);

	std::vector<std::string> text;
	text.emplace_back("Move around: Mouse + RMB");
	text.emplace_back("Zoom in/out: Scroll Wheel");
	text.emplace_back("UI Intercations: LMB");

	std::unique_ptr<SingleUIWindow> controls = std::make_unique<UIStandard>(spec, text);

	uiWindows.emplace_back(std::move(controls));
}

void UILayer::initGeneralInfo(int number)
{
	ImVec2 pos{ 10.f, 10.f };
	ImVec2 size{ 216.f, 25.f };
	UIWindowSpec spec(UIWindowInstance::GENERAL_INFO, "info", pos, size, 0.5f, false, true, true, true);

	std::vector<std::string> text;
	text.emplace_back("Space Object in Total: " + std::to_string(number));

	std::unique_ptr<SingleUIWindow> info = std::make_unique<UIStandard>(spec, text);

	uiWindows.emplace_back(std::move(info));
}

void UILayer::initObjectList()
{
}

void UILayer::initMenu()
{
	ImVec2 pos{ 1160.f, 10.f };
	ImVec2 size{ 100.f, 180.f };
	UIWindowSpec spec(UIWindowInstance::EXIT, "PANEL", pos, size, 0.f, true, true, false, false);

	ImVec4 exitButtonColor1(1.f, .1f, .0f, 1.f);
	ImVec4 exitButtonColor2(1.f, .28f, .14f, 1.f);
	ImVec4 exitButtonColor3(1.f, .48f, .14f, 1.f);

	ImVec4 buttonColor1(.1f, .2f, .8f, 1.f);
	ImVec4 buttonColor2(0.f, 0.03f, 0.18f, 1.f);
	ImVec4 buttonColor3(.33f, .78f, .8f, 1.f);

	std::vector<UIButton> buttons;
	buttons.emplace_back(UIButton(UIWindowInstance::EXIT,         "   EXIT    ", exitButtonColor1, exitButtonColor2, exitButtonColor3));
	buttons.emplace_back(UIButton(UIWindowInstance::GENERAL_INFO, "INFORMATION", buttonColor1, buttonColor2, buttonColor3));
	buttons.emplace_back(UIButton(UIWindowInstance::OBJECTS_LIST, "OBJECT LIST", buttonColor1, buttonColor2, buttonColor3));
	buttons.emplace_back(UIButton(UIWindowInstance::TIME_LINE,    " PLAY BACK ", buttonColor1, buttonColor2, buttonColor3));
	buttons.emplace_back(UIButton(UIWindowInstance::CONTROLS,     " CONTROLS  ", buttonColor1, buttonColor2, buttonColor3));

	std::unique_ptr<SingleUIWindow> info = std::make_unique<UIButtonList>(spec, buttons);

	uiWindows.emplace_back(std::move(info));
}

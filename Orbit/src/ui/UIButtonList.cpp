#include "pch.h"
#include "UIButtonList.h"

UIButtonList::UIButtonList(const UIWindowSpec& uiSpec, const std::vector<UIButton>& buttons)
	: SingleUIWindow(uiSpec), content(buttons)
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | 
		ImGuiWindowFlags_AlwaysAutoResize | 
		ImGuiWindowFlags_NoSavedSettings | 
		ImGuiWindowFlags_NoFocusOnAppearing | 
		ImGuiWindowFlags_NoNav;
}

void UIButtonList::onUpdate()
{
	ImGui::SetNextWindowBgAlpha(specification.transparency);
	//ImGui::SetNextWindowPos(specification.position);
	ImGui::SetNextWindowSize(specification.size);

	const char* newTitle = specification.title.c_str();
	ImGui::Begin(newTitle, &specification.open, window_flags);

	ImGui::PushID(0);
	std::cout << "new" << content[0].clicked << std::endl;
	ImGui::Checkbox("", &content[0].clicked);
	std::cout << content[0].clicked << std::endl;
	ImGui::PopID();
	
	ImGui::PushID(1);
	std::cout << "new" << content[1].clicked << std::endl;
	ImGui::Checkbox("", &content[1].clicked);
	std::cout << content[1].clicked << std::endl;
	ImGui::PopID();
	
	ImGui::PushID(2);
	std::cout << "new" << content[2].clicked << std::endl;
	ImGui::Checkbox("", &content[2].clicked);
	std::cout << content[2].clicked << std::endl;
	ImGui::PopID();

	//int i = 0;
	//for (auto& button : content)
	//{
	//	ImGui::PushID(i);
	//	ImGui::PushStyleColor(ImGuiCol_Button, button.colorStandard);
	//	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, button.colorHighlight);
	//
	//	//if (specification.open)
	//	//{
	//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, button.colorActive);
	//	//}
	//
	//	if (ImGui::Checkbox("", &button.clicked)) button.clicked ? button.clicked = false : button.clicked = true;
	//	ImGui::SameLine();
	//
	//	ImGui::Button(button.text.c_str());
	//	//{
	//	//	button.clicked ? button.clicked = false : button.clicked = true;
	//	//	//std::cout << button.clicked << std::endl;
	//	//}
	//	ImGui::PopID();
	//	i++;
	//	//ImGui::PopStyleColor(3);		
	//}

	ImGui::End();
}

void UIButtonList::show(bool show)
{
	specification.open = show;
}

float UIButtonList::getValue() const
{
	return 0.f;
}

UIType UIButtonList::getType() const
{
	return type;
}

std::vector<UIButton> UIButtonList::getButtons() const
{
	return content;
}

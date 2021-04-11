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

	int i = 0;
	for (auto& button : content)
	{
		ImGui::PushID(i);
		ImGui::PushStyleColor(ImGuiCol_Button, button.colorStandard);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, button.colorHighlight);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, button.colorActive);

		if (ImGui::Button(button.text.c_str()))
		{
			button.clicked ? button.clicked = false : button.clicked = true;
			button.change = true;
		}

		ImGui::PopStyleColor(3);		
		ImGui::PopID();
		i++;
	}

	ImGui::End();
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

#include "pch.h"
#include "UISlider.h"

UISlider::UISlider(const UIWindowSpec& uiSpec, const std::string& text_, int min_, int max_)
	: SingleUIWindow(uiSpec), text(text_), min(min_), max(max_)
{
}

UISlider::UISlider(const UIWindowSpec& uiSpec, const std::string& text_, int min_, int max_, std::unique_ptr<UIButton>& button_)
	: SingleUIWindow(uiSpec), text(text_), min(min_), max(max_), button(std::move(button_))
{
}

void UISlider::onUpdate()
{
	if (specification.open)
	{
		ImGui::SetNextWindowBgAlpha(specification.transparency);
		ImGui::SetNextWindowPos(specification.position);
		ImGui::SetNextWindowSize(specification.size);

		const char* newTitle = specification.title.c_str();

		ImGui::Begin(newTitle, &specification.open, window_flags);

		if (button != nullptr)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, button->colorStandard);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, button->colorHighlight);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, button->colorActive);
			
			if (ImGui::Button(button->textActive.c_str()))
			{
				if (button->clicked)
				{
					button->clicked = false;
					button->textActive = button->textSecond;
				}
				else
				{
					button->clicked = true;
					button->textActive = button->text;
				}
				
			}

			ImGui::SameLine();
		}

		ImGui::SliderInt(text.c_str(), &value, min, max);

		ImGui::End();
	}
}

void UISlider::show(bool show)
{
	specification.open = show;
}

int UISlider::getValue() const
{
	return value;
}

UIType UISlider::getType() const
{
	return type;
}

bool UISlider::isButtonClicked() const
{
	return button->clicked;
}

#include "pch.h"
#include "UISlider.h"

UISlider::UISlider(const UIWindowSpec& uiSpec, const std::string& text_, float min_, float max_)
	: SingleUIWindow(uiSpec), text(text_), min(min_), max(max_)
{
}

void UISlider::onUpdate()
{
	if (specification.open)
	{
		ImGui::SetNextWindowBgAlpha(specification.transparency);
		//ImGui::SetNextWindowPos(specification.position);
		ImGui::SetNextWindowSize(specification.size);

		const char* newTitle = specification.title.c_str();

		ImGui::Begin(newTitle, &specification.open, window_flags);

		ImGui::SliderFloat(text.c_str(), &value, min, max);

		ImGui::End();
	}
}

void UISlider::show(bool show)
{
	specification.open = show;
}

float UISlider::getValue() const 
{
	return value;
}

UIType UISlider::getType() const
{
	return type;
}

#include "pch.h"
#include "UIStandard.h"

UIStandard::UIStandard(const UIWindowSpec& uiSpec, const std::vector<std::string>& text_)
	: SingleUIWindow(uiSpec), content(text_)
{
}

void UIStandard::onUpdate()
{
	if (specification.open)
	{
		ImGui::SetNextWindowBgAlpha(specification.transparency);
		ImGui::SetNextWindowPos(specification.position);
		ImGui::SetNextWindowSize(specification.size);

		const char* newTitle = specification.title.c_str();
		ImGui::Begin(newTitle, &specification.open, window_flags);

		for (const auto& text : content)
		{
			ImGui::Text(text.c_str());
		}

		ImGui::End();
	}
}

void UIStandard::show(bool show)
{
	specification.open = show;
}

int UIStandard::getValue() const
{
	return 0.f;
}

UIType UIStandard::getType() const
{
	return type;
}

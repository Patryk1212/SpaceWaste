#pragma once

#include <Engine.h>

#include "UIEnums.h"

struct UIButton
{
	UIWindowInstance type = UIWindowInstance::NONE;
	
	std::string text;
	std::string textSecond;
	std::string textActive;

	ImVec4 colorStandard;
	ImVec4 colorHighlight;
	ImVec4 colorActive;

	bool change = false;
	bool clicked = true;

	UIButton(const std::string& text_, const std::string& textSecond_, const ImVec4& colorStandard_, const ImVec4& colorHighlight_, const ImVec4& colorActive_)
		: text(text_), textActive(text_), textSecond(textSecond_), colorStandard(colorStandard_), colorHighlight(colorHighlight_), colorActive(colorActive_) {}

	UIButton(const UIWindowInstance& type_, const std::string& text_, const ImVec4& colorStandard_, const ImVec4& colorHighlight_, const ImVec4& colorActive_)
		: type(type_), text(text_), colorStandard(colorStandard_), colorHighlight(colorHighlight_), colorActive(colorActive_) {}
};

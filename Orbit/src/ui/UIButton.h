#pragma once

#include <Engine.h>

#include "UIEnums.h"

struct UIButton
{
	UIWindowInstance type = UIWindowInstance::NONE;
	std::string text;
	ImVec4 colorStandard;
	ImVec4 colorHighlight;
	ImVec4 colorActive;

	bool change = false;
	bool clicked = true;

	UIButton(const UIWindowInstance& type_, const std::string& text_, const ImVec4& colorStandard_, const ImVec4& colorHighlight_, const ImVec4& colorActive_)
		: type(type_), text(text_), colorStandard(colorStandard_), colorHighlight(colorHighlight_), colorActive(colorActive_) {}
};

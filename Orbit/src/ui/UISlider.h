#pragma once

#include "SingleUIWindow.h"

class UISlider : public SingleUIWindow
{
public:
	UISlider(const UIWindowSpec& uiSpec, const std::string& text_, float min_, float max_);
	~UISlider() = default;

	virtual void onUpdate() override;
	virtual void show(bool show) override;
	virtual float getValue() const override;
	virtual UIType getType() const override;

private:
	UIType type = UIType::SLIDER;

private:
	std::string text;
	float value = 0;
	float min = 0;
	float max = 0;
};
